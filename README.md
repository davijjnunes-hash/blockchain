# Blockchain em C

Implementação educacional de uma blockchain em C puro (C11), usando SHA-256 da OpenSSL para hashear os blocos. O projeto serve como estudo prático de estruturas de dados, criptografia e build com CMake.

## Estado atual

- [x] Estrutura do bloco (`Block`)
- [x] Hash do bloco com SHA-256 (`block_hash`)
- [x] Criação e impressão do bloco gênese
- [ ] Mineração (proof-of-work com `nonce` e `difficulty`)
- [ ] Vários blocos encadeados (`previous_hash`)
- [ ] Validação da chain

## O bloco

| Campo         | Tipo       | Para quê                                |
|---------------|------------|-----------------------------------------|
| index         | `uint32_t` | Posição do bloco na chain (0 = gênese)  |
| timestamp     | `time_t`   | Quando foi criado                       |
| data[256]     | `char[]`   | O payload (depois virarão transações)   |
| previous_hash | `char[65]` | Hash do bloco anterior — a corrente     |
| nonce         | `uint64_t` | Contador de mineração                   |
| difficulty    | `uint32_t` | Zeros exigidos no início do hash        |
| hash          | `char[65]` | O hash do bloco (64 hex chars + `\0`)   |

O hash é calculado sobre os campos do bloco serializados (`index|timestamp|difficulty|data|previous_hash|nonce`) com `SHA256()`, e convertido para hexadecimal.

## Requisitos

- Compilador C com suporte a C11 (GCC, Clang...)
- CMake >= 3.16
- OpenSSL (libcrypto)

No Debian/Ubuntu:

```bash
sudo apt install build-essential cmake libssl-dev
```

## Compilando e executando

```bash
cmake -S . -B build    # configura (gera Makefiles + compile_commands.json)
cmake --build build    # compila e linka
./build/blockchain     # executa
```

Saída esperada:

```
Bloco #0
Data:         Genesis Block
Hash anterior: 
Hash:          <hash SHA-256 do bloco>
```

## Estrutura do projeto

```
.
├── CMakeLists.txt        # Configuração do build (C11 + OpenSSL)
├── include/
│   └── blockchain.h      # Struct Block e protótipos
├── src/
│   ├── block.c           # Implementação do hash do bloco
│   └── main.c            # Criação do bloco gênese
├── docs/
│   ├── block.md          # Conceitos de blockchain e do bloco
│   └── cmake.md          # Explicação do CMakeLists.txt
└── build/                # Artefatos de build (ignorado pelo git)
```

## Documentação

- [docs/block.md](docs/block.md) — conceito de blockchain e da struct `Block`
- [docs/cmake.md](docs/cmake.md) — configuração do projeto C com CMake
