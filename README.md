# Beanz 2.0

Beanz 2.0 is a C++ text adventure that can run in a terminal or through a React web interface.

## Terminal game

Build and run the game from this directory:

```sh
make Linux
./bin/beanz2
```

The terminal remains the default output mode. On Windows, use the `build` Make target.

## Web game

The web app uses React, Vite, Tailwind CSS, and a small Node.js HTTP bridge. The bridge starts the C++ game with `BEANZ_OUTPUT_MODE=web`; game output and player input are exchanged over HTTP.

Requirements: Node.js 18+, npm, GNU Make, and a C++ compiler.

```sh
cd web
npm install
npm run dev
```

Open the Vite URL printed in the terminal (normally `http://localhost:5173`). The bridge starts the game automatically and proxies browser requests to the local game process.

To build and serve the production web app:

```sh
npm run build
npm start
```

The bridge listens on port `4174` by default. Set `BEANZ_WEB_PORT` to change it; `PORT` is also accepted when deploying. The C++ process uses `BEANZ_WEB_HOST` and `BEANZ_WEB_PORT` for its HTTP connection. `BEANZ_OUTPUT_MODE=web` enables web output; any other value leaves normal terminal output enabled.
