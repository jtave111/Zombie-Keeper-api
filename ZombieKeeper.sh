#!/usr/bin/env bash

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

cleanup() {
    kill "$API_PID" "$CLIENT_PID" 2>/dev/null
}

trap cleanup EXIT INT TERM

echo "Iniciando API..."
(cd "$ROOT_DIR/ZombieKeeper-Api" && \
    mvn spring-boot:run -Dspring-boot.run.jvmArguments=--enable-preview) &
API_PID=$!

echo "Aguardando API na porta 8080..."
until curl --silent http://localhost:8080/actuator/health >/dev/null; do
    if ! kill -0 "$API_PID" 2>/dev/null; then
        echo "A API falhou ao iniciar."
        exit 1
    fi
    sleep 1
done

echo "Iniciando cliente..."
(cd "$ROOT_DIR/ZombieKeeper-Client" && npm run tauri dev) &
CLIENT_PID=$!

echo "ZombieKeeper iniciado. Use Ctrl+C para encerrar."
wait
