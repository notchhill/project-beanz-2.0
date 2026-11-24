import { spawn } from 'node:child_process';
import { once } from 'node:events';
import { setTimeout as delay } from 'node:timers/promises';
import { fileURLToPath } from 'node:url';
import { join } from 'node:path';

const webDirectory = fileURLToPath(new URL('.', import.meta.url));
const projectDirectory = join(webDirectory, '..');
const port = process.env.BEANZ_WEB_PORT || '4174';
const children = [];

const stopChildren = () => {
  for (const child of children) {
    if (child.exitCode === null && child.signalCode === null) child.kill('SIGTERM');
  }
};

process.on('SIGINT', stopChildren);
process.on('SIGTERM', stopChildren);

const build = spawn('make', ['Linux'], { cwd: projectDirectory, stdio: 'inherit' });
const [buildCode] = await once(build, 'exit');
if (buildCode !== 0) {
  process.exitCode = buildCode || 1;
} else {
  const backend = spawn(process.execPath, ['server.js'], {
    cwd: webDirectory,
    env: { ...process.env, BEANZ_WEB_PORT: port },
    stdio: 'inherit'
  });
  children.push(backend);

  let ready = false;
  for (let attempt = 0; attempt < 40 && !ready; attempt += 1) {
    try {
      const response = await fetch(`http://127.0.0.1:${port}/api/health`);
      ready = response.ok;
    } catch {
      await delay(250);
    }
    if (backend.exitCode !== null) break;
  }

  if (!ready) {
    console.error('Could not start the Beanz HTTP bridge.');
    stopChildren();
    process.exitCode = 1;
  } else {
    const vite = spawn(process.execPath, [join(webDirectory, 'node_modules', 'vite', 'bin', 'vite.js'), '--host', '0.0.0.0'], {
      cwd: webDirectory,
      env: { ...process.env, BEANZ_WEB_PORT: port },
      stdio: 'inherit'
    });
    children.push(vite);
    const onChildExit = (code) => {
      if (code !== null && code !== 0) process.exitCode = code;
      stopChildren();
    };
    backend.on('exit', onChildExit);
    vite.on('exit', onChildExit);
  }
}
