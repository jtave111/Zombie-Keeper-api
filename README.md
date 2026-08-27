<div align="center">

# MERUM

### Security Operations Platform

**Visibilidade, controle e automação para laboratórios de segurança.**

![Java](https://img.shields.io/badge/Java-21-E76F00?style=flat-square&logo=openjdk&logoColor=white)
![Spring Boot](https://img.shields.io/badge/Spring_Boot-4.0-6DB33F?style=flat-square&logo=springboot&logoColor=white)
![React](https://img.shields.io/badge/React-19-20232A?style=flat-square&logo=react&logoColor=61DAFB)
![Tauri](https://img.shields.io/badge/Tauri-2-24C8DB?style=flat-square&logo=tauri&logoColor=white)
![Rust](https://img.shields.io/badge/Rust-stable-000000?style=flat-square&logo=rust&logoColor=white)

</div>

---

Merum é uma plataforma C2 full-stack para pesquisa, treinamento e operações de segurança autorizadas. O projeto reúne uma API central, um cliente desktop multiplataforma, ferramentas nativas e automações em um único monorepo.

> [!IMPORTANT]
> Use o Merum somente em sistemas próprios ou com autorização explícita. O operador é responsável por cumprir as leis, políticas e regras aplicáveis ao ambiente analisado.

## Visão geral

```text
                            ┌─────────────────────┐
                            │    Merum Client     │
                            │ React 19 · Tauri 2  │
                            └──────────┬──────────┘
                                       │ REST / WebSocket
                            ┌──────────▼──────────┐
                            │      Merum API      │
                            │ Spring Boot · Java  │
                            └──────┬────────┬─────┘
                                   │        │
                         ┌─────────▼──┐  ┌──▼──────────────┐
                         │  Database  │  │ Merum Arsenal   │
                         │ MySQL / H2 │  │ C++ · Go · Rust │
                         └────────────┘  └─────────────────┘
```

| Componente | Responsabilidade | Tecnologias |
| --- | --- | --- |
| `Merum-Api` | Autenticação, agentes, telemetria, sessões e WebSockets | Java 21, Spring Boot 4, JPA, JWT |
| `Merum-Client` | Interface desktop do operador | React 19, TypeScript, Vite, Tauri 2 |
| `Merum-Arsenal` | Ferramentas nativas de descoberta e operação | C++17, CMake, Go, Rust |
| `Merum-Automations` | Fluxos auxiliares e automações | Python 3 |

## Recursos

- Dashboard operacional com métricas e visão geográfica
- Gerenciamento de agentes, processos e sessões
- Terminal interativo via WebSocket
- Descoberta, fingerprint e visualização de rede
- Geração e organização de payloads para laboratório
- Gestão de usuários com autenticação JWT
- Arsenal modular para ferramentas nativas
- Cliente desktop para Linux, Windows e macOS

## Começando

### Pré-requisitos

- Java 21
- Maven 3.9+
- Node.js 20+ e npm
- Rust stable e Cargo
- MySQL 8 (ou H2 para desenvolvimento)
- Dependências de sistema exigidas pelo Tauri 2

### 1. Configure a API

```bash
cp Merum-Api/.env.example Merum-Api/.env
```

Edite `Merum-Api/.env` e defina, no mínimo, as credenciais do banco, `JWT_SECRET`, `ENCRYPTION_KEY` e o usuário administrador inicial. Gere um segredo JWT com:

```bash
openssl rand -hex 32
```

### 2. Instale o cliente

```bash
cd Merum-Client
npm install
cd ..
```

### 3. Inicie a plataforma

```bash
chmod +x Merum.sh
./Merum.sh
```

O launcher inicia a API, aguarda o health check em `http://localhost:8080/actuator/health` e abre o cliente desktop.

## Desenvolvimento

Execute os componentes separadamente quando precisar de recarregamento rápido ou logs isolados.

### API

```bash
cd Merum-Api
./mvnw spring-boot:run -Dspring-boot.run.jvmArguments=--enable-preview
```

### Interface web

```bash
cd Merum-Client
npm run dev
```

### Aplicação desktop

```bash
cd Merum-Client
npm run tauri dev
```

### Arsenal nativo

```bash
cd Merum-Arsenal
cmake -S . -B build
cmake --build build
```

## Build e verificações

```bash
# API e testes Java
./Merum-Api/mvnw -f pom.xml test

# Front-end
cd Merum-Client && npm run build

# Camada Tauri/Rust
cd Merum-Client/src-tauri && cargo check
```

Para gerar o aplicativo desktop distribuível:

```bash
cd Merum-Client
npm run tauri build
```

## Estrutura do repositório

```text
Merum/
├── Merum-Api/           # API e servidor C2
├── Merum-Client/        # React, Vite e aplicação Tauri
├── Merum-Arsenal/       # Ferramentas nativas e scanners
├── Merum-Automations/   # Automações Python
├── Ideas/               # Propostas e estudos futuros
├── Learning/            # Material de aprendizado
├── Merum.sh             # Inicialização integrada
├── HELP.md              # Referência rápida
└── MONOREPO.md          # Detalhes da arquitetura
```

## Segurança

- Nunca versione `.env`, tokens, chaves privadas ou credenciais.
- Troque os valores de exemplo antes de expor a API em qualquer rede.
- Restrinja `CORS_ALLOWED_ORIGINS` aos clientes confiáveis.
- Mantenha os limites de upload e retenção de logs adequados ao ambiente.
- Prefira redes isoladas e dados sintéticos durante testes.

## Documentação

- [`HELP.md`](HELP.md) — comandos e resolução de problemas
- [`MONOREPO.md`](MONOREPO.md) — organização e decisões de arquitetura
- [`Merum-Arsenal/README.md`](Merum-Arsenal/README.md) — build das ferramentas nativas
- [`Merum-Automations/README.md`](Merum-Automations/README.md) — automações disponíveis

---

<div align="center">

**Merum** · construído para compreender os dois lados da infraestrutura.

</div>
