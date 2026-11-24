import { randomBytes, timingSafeEqual } from 'node:crypto';
import { spawn } from 'node:child_process';
import { createReadStream, existsSync, readFileSync, statSync } from 'node:fs';
import { createServer } from 'node:http';
import { extname, join, normalize, resolve } from 'node:path';
import { fileURLToPath } from 'node:url';

const webDirectory = fileURLToPath(new URL('.', import.meta.url));
const projectDirectory = resolve(webDirectory, '..');
const staticDirectory = join(webDirectory, 'dist');
const port = Number(process.env.BEANZ_WEB_PORT || process.env.PORT || 4174);
const events = [];
const queuedInputs = [];
const bridgeToken = randomBytes(32).toString('hex');
const saveCookieName = 'beanz_save';
const maxSaveCookieLength = 3800;
let nextEventId = 1;
let gameProcess;
let gameExit = null;
let gameError = '';
let webSaveData = '';
let saveCookiePending = false;
let saveCookieAttempts = 0;
let saveCookieError = '';

const mimeTypes = {
  '.css': 'text/css; charset=utf-8',
  '.html': 'text/html; charset=utf-8',
  '.ico': 'image/x-icon',
  '.js': 'text/javascript; charset=utf-8',
  '.json': 'application/json; charset=utf-8',
  '.svg': 'image/svg+xml'
};

const sendJson = (response, status, value, headers = {}) => {
  const body = JSON.stringify(value);
  response.writeHead(status, {
    'Content-Type': 'application/json; charset=utf-8',
    'Content-Length': Buffer.byteLength(body),
    Connection: 'close',
    'Cache-Control': 'no-store',
    ...headers
  });
  response.end(body);
};

const readBrowserSave = (cookieHeader = '') => {
  const saveCookie = cookieHeader.split(';')
    .map((cookie) => cookie.trim())
    .find((cookie) => cookie.startsWith(`${saveCookieName}=`));
  if (!saveCookie) return null;

  const encoded = saveCookie.slice(saveCookieName.length + 1);
  if (!encoded || encoded.length > maxSaveCookieLength || !/^[A-Za-z0-9_-]+$/.test(encoded)) {
    throw new Error('The browser save cookie is invalid or too large.');
  }
  const data = Buffer.from(encoded, 'base64url');
  if (data.toString('base64url') !== encoded) {
    throw new Error('The browser save cookie is invalid.');
  }
  return data.toString('utf8');
};

const readLegacySave = () => {
  const savePath = join(projectDirectory, 'resource', 'save.txt');
  return existsSync(savePath) ? readFileSync(savePath, 'utf8') : '';
};

const startGame = (request) => {
  if (gameProcess) return;

  const browserSave = readBrowserSave(request.headers.cookie);
  webSaveData = browserSave ?? readLegacySave();
  if (browserSave === null && webSaveData) {
    const encoded = Buffer.from(webSaveData, 'utf8').toString('base64url');
    if (encoded.length <= maxSaveCookieLength) {
      saveCookiePending = true;
      saveCookieAttempts = 0;
    } else {
      saveCookieError = 'The existing save is too large to fit in a browser cookie.';
    }
  }

  gameProcess = spawn(join(projectDirectory, 'bin', 'beanz2'), [], {
    cwd: projectDirectory,
    env: {
      ...process.env,
      BEANZ_OUTPUT_MODE: 'web',
      BEANZ_WEB_HOST: '127.0.0.1',
      BEANZ_WEB_PORT: String(port),
      BEANZ_WEB_TOKEN: bridgeToken
    },
    stdio: ['ignore', 'ignore', 'inherit']
  });

  gameProcess.on('error', (error) => {
    gameError = `Could not start the game: ${error.message}`;
    gameExit = { code: 1, signal: null };
    console.error(gameError);
  });
  gameProcess.on('exit', (code, signal) => {
    gameExit = { code, signal };
    if (code !== 0 && signal !== 'SIGTERM') {
      gameError = `The game exited unexpectedly${code === null ? ` (${signal})` : ` with code ${code}`}.`;
    }
  });
};

const readJson = (request) => new Promise((resolveBody, rejectBody) => {
  let body = '';
  request.setEncoding('utf8');
  request.on('data', (chunk) => {
    body += chunk;
    if (body.length > 1024 * 1024) {
      rejectBody(new Error('Request body is too large.'));
      request.destroy();
    }
  });
  request.on('end', () => {
    try {
      resolveBody(JSON.parse(body));
    } catch {
      rejectBody(new Error('Request body must be valid JSON.'));
    }
  });
  request.on('error', rejectBody);
});

const mimeType = (filePath) => mimeTypes[extname(filePath)] || 'application/octet-stream';

const isGameBridgeRequest = (request) => {
  const provided = Buffer.from(request.headers['x-beanz-bridge-token'] || '');
  const expected = Buffer.from(bridgeToken);
  return provided.length === expected.length && timingSafeEqual(provided, expected);
};

const serveStatic = (request, response, pathname) => {
  const requestedPath = pathname === '/' ? '/index.html' : pathname;
  const resolvedPath = resolve(staticDirectory, `.${normalize(requestedPath)}`);
  if (!resolvedPath.startsWith(`${staticDirectory}/`) && resolvedPath !== staticDirectory) {
    sendJson(response, 400, { error: 'Invalid path.' });
    return;
  }
  const filePath = existsSync(resolvedPath) && statSync(resolvedPath).isFile()
    ? resolvedPath
    : join(staticDirectory, 'index.html');
  if (!existsSync(filePath)) {
    sendJson(response, 404, { error: 'Web assets are not built. Run npm run build first.' });
    return;
  }
  response.writeHead(200, { 'Content-Type': mimeType(filePath) });
  createReadStream(filePath).pipe(response);
};

const server = createServer(async (request, response) => {
  const url = new URL(request.url, `http://${request.headers.host || 'localhost'}`);
  try {
    if (request.method === 'GET' && url.pathname === '/api/health') {
      sendJson(response, 200, { ready: true });
      return;
    }

    if (request.method === 'GET' && url.pathname === '/api/events') {
      startGame(request);
      const after = Number(url.searchParams.get('after') || 0);
      if (!Number.isSafeInteger(after) || after < 0) {
        sendJson(response, 400, { error: 'The event cursor is invalid.' });
        return;
      }
      let saveCookieStatus = null;
      const headers = {};
      if (saveCookiePending) {
        const browserSave = readBrowserSave(request.headers.cookie);
        if (browserSave === webSaveData) {
          saveCookiePending = false;
          saveCookieAttempts = 0;
          saveCookieError = '';
          saveCookieStatus = 'stored';
        } else if (saveCookieAttempts < 3) {
          const encoded = Buffer.from(webSaveData, 'utf8').toString('base64url');
          const secure = request.socket.encrypted || request.headers['x-forwarded-proto'] === 'https'
            ? '; Secure'
            : '';
          headers['Set-Cookie'] = `${saveCookieName}=${encoded}; Path=/; Max-Age=31536000; SameSite=Lax; HttpOnly${secure}`;
          saveCookieAttempts++;
        } else {
          saveCookiePending = false;
          saveCookieError = 'Your browser did not accept the save cookie.';
          saveCookieStatus = 'error';
        }
      } else if (saveCookieError) {
        saveCookieStatus = 'error';
      }
      sendJson(response, 200, {
        events: events.filter((event) => event.id > after),
        done: gameExit !== null,
        exitCode: gameExit?.code ?? null,
        error: gameError,
        saveCookieStatus
      }, headers);
      return;
    }

    if (request.method === 'GET' && url.pathname === '/api/save') {
      if (!isGameBridgeRequest(request)) {
        sendJson(response, 401, { error: 'Game bridge authentication failed.' });
        return;
      }
      if (!webSaveData) {
        response.writeHead(204, { Connection: 'close', 'Cache-Control': 'no-store' });
        response.end();
        return;
      }
      response.writeHead(200, {
        'Content-Type': 'text/plain; charset=utf-8',
        'Content-Length': Buffer.byteLength(webSaveData),
        Connection: 'close',
        'Cache-Control': 'no-store'
      });
      response.end(webSaveData);
      return;
    }

    if (request.method === 'POST' && url.pathname === '/api/save') {
      if (!isGameBridgeRequest(request)) {
        sendJson(response, 401, { error: 'Game bridge authentication failed.' });
        return;
      }
      const body = await readJson(request);
      if (typeof body.data !== 'string' || !body.data) {
        sendJson(response, 400, { error: 'Save data must be a non-empty string.' });
        return;
      }
      const encoded = Buffer.from(body.data, 'utf8').toString('base64url');
      if (encoded.length > maxSaveCookieLength) {
        sendJson(response, 413, { error: 'Save data is too large to fit in a browser cookie.' });
        return;
      }
      webSaveData = body.data;
      saveCookiePending = true;
      saveCookieAttempts = 0;
      saveCookieError = '';
      sendJson(response, 202, { accepted: true });
      return;
    }

    if (request.method === 'POST' && url.pathname === '/api/output') {
      if (!isGameBridgeRequest(request)) {
        sendJson(response, 401, { error: 'Game bridge authentication failed.' });
        return;
      }
      const body = await readJson(request);
      if (typeof body.text !== 'string') {
        sendJson(response, 400, { error: 'Output text must be a string.' });
        return;
      }
      events.push({ id: nextEventId++, text: body.text });
      sendJson(response, 202, { accepted: true });
      return;
    }

    if (request.method === 'GET' && url.pathname === '/api/input') {
      if (!isGameBridgeRequest(request)) {
        sendJson(response, 401, { error: 'Game bridge authentication failed.' });
        return;
      }
      if (queuedInputs.length) {
        const input = queuedInputs.shift();
        response.writeHead(200, {
          'Content-Type': 'text/plain; charset=utf-8',
          'Content-Length': Buffer.byteLength(input),
          Connection: 'close'
        });
        response.end(input);
      } else if (gameExit !== null) {
        sendJson(response, 410, { error: 'The game is no longer accepting input.' });
      } else {
        response.writeHead(204, { Connection: 'close' });
        response.end();
      }
      return;
    }

    if (request.method === 'POST' && url.pathname === '/api/input') {
      if (gameExit !== null || !gameProcess) {
        sendJson(response, 409, { error: 'The game is not running.' });
        return;
      }
      const body = await readJson(request);
      const inputs = Array.isArray(body.inputs) ? body.inputs : [body.input];
      if (!inputs.length || inputs.length > 8 || inputs.some((input) =>
        typeof input !== 'string' || !input.trim() || /[\r\n]/.test(input)
      )) {
        sendJson(response, 400, { error: 'Enter between one and eight non-empty commands.' });
        return;
      }
      if (queuedInputs.length) {
        sendJson(response, 409, { error: 'The previous choice is still being processed.' });
        return;
      }
      queuedInputs.push(...inputs.map((input) => input.trim()));
      sendJson(response, 202, { accepted: true, queued: inputs.length });
      return;
    }

    if (request.method === 'GET' && !url.pathname.startsWith('/api/')) {
      serveStatic(request, response, url.pathname);
      return;
    }

    sendJson(response, 404, { error: 'Not found.' });
  } catch (error) {
    if (!response.headersSent) {
      sendJson(response, 400, { error: error.message || 'Invalid request.' });
    } else {
      response.destroy(error);
    }
  }
});

server.listen(port, process.env.BEANZ_WEB_BIND || '0.0.0.0', () => {
  console.log(`Beanz web server listening on port ${port}`);
});

const stop = () => {
  if (gameProcess && gameExit === null) {
    gameProcess.kill('SIGTERM');
  }
  server.close(() => process.exit(0));
  setTimeout(() => process.exit(1), 3000).unref();
};

process.on('SIGINT', stop);
process.on('SIGTERM', stop);
