FROM node:22-bookworm-slim AS build

RUN apt-get update \
    && apt-get install -y --no-install-recommends build-essential \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app

COPY Makefile ./
COPY include ./include
COPY src ./src
COPY resource ./resource

RUN mkdir -p build bin && make Linux

COPY web/package.json web/package-lock.json ./web/
WORKDIR /app/web
RUN npm ci
COPY web/ ./
RUN npm run build

FROM node:22-bookworm-slim AS runtime

ENV NODE_ENV=production
ENV BEANZ_WEB_BIND=0.0.0.0
ENV PORT=10000

WORKDIR /app

COPY --from=build --chown=node:node /app/bin/beanz2 ./bin/beanz2
COPY --from=build --chown=node:node /app/resource ./resource
COPY --from=build --chown=node:node /app/web/server.js ./web/server.js
COPY --from=build --chown=node:node /app/web/dist ./web/dist

USER node

EXPOSE 10000

CMD ["node", "web/server.js"]
