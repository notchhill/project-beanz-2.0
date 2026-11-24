import { defineConfig } from 'vite';
import react from '@vitejs/plugin-react';

const bridgePort = process.env.BEANZ_WEB_PORT || '4174';

export default defineConfig({
  plugins: [react()],
  server: {
    proxy: {
      '/api': {
        target: `http://127.0.0.1:${bridgePort}`,
        changeOrigin: true
      }
    }
  }
});
