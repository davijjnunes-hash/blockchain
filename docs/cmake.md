# Configuração de projetos C com CMake

Este documento explica as configurações do `CMakeLists.txt` deste projeto e por que cada uma existe.

## O básico

```cmake
cmake_minimum_required(VERSION 3.16)

project(blockchain
    VERSION 0.1.0
    LANGUAGES C
)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
```

| Configuração | Efeito |
|---|---|
| `LANGUAGES C` | Diz que é um projeto C (o padrão do CMake é C e C++) |
| `CMAKE_C_STANDARD 11` | Compila com `-std=c11` |
| `CMAKE_C_STANDARD_REQUIRED ON` | Falha se o compilador não suportar C11, em vez de cair para uma versão anterior |
| `CMAKE_C_EXTENSIONS OFF` | Sem extensões do GCC (`-std=c11` puro, não `gnu11`). Código portátil |

## Adicionando fontes

```cmake
add_executable(blockchain
    src/main.c
    src/block.c
)
```

Todo `.c` que compõe o executável precisa estar listado aqui. Arquivos fora da lista **não são compilados** — por isso erros nesses arquivos só aparecem quando entram no build.

## Caminho de include (`#include "..."` não acha meu header)

Com `#include "blockchain.h"` (aspas), o compilador procura:

1. Na pasta do arquivo que está sendo compilado (`src/`)
2. Nas pastas passadas com a flag `-I`

Como o header está em `include/`, a busca falha na etapa 1. A correção é:

```cmake
target_include_directories(blockchain PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
```

O CMake traduz isso para `-I<projeto>/include`. `PRIVATE` significa que só este alvo usa esse caminho (use `PUBLIC` se outras bibliotecas que linkarem com você também precisarem).

## Linkando bibliotecas (OpenSSL)

```cmake
find_package(OpenSSL REQUIRED)
target_link_libraries(blockchain PRIVATE OpenSSL::Crypto)
```

| Parte | Para quê |
|---|---|
| `find_package(OpenSSL REQUIRED)` | Procura a OpenSSL instalada no sistema e cria os alvos importados `OpenSSL::Crypto` e `OpenSSL::SSL`. Sem essa linha, o `target_link_libraries` falha com *"target was not found"* |
| `OpenSSL::Crypto` | A lib de criptografia (hashes SHA-256, etc.). Já traz o caminho de includes junto — não precisa de `target_include_directories` para ela |
| `REQUIRED` | Aborta o configure se a OpenSSL não estiver instalada |

> Detalhe: no código C usa-se `#include <openssl/sha.h>` e a função `SHA256()` — é a libcrypto que as fornece.

## Erros no editor (Zed / clangd)

O clangd (servidor de linguagem do Zed) não lê o `CMakeLists.txt` — ele precisa do banco de compilação:

```cmake
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
```

Isso gera `build/compile_commands.json` com os comandos exatos de compilação (includes, defines, flags). O clangd o procura automaticamente na pasta `build/` e os "erros fantasmas" do editor somem.

Sempre que o build for recriado do zero, o arquivo é regenerado no configure.

## Fluxo de build

```bash
cmake -S . -B build    # configura (gera Makefiles + compile_commands.json)
cmake --build build    # compila e linka
./build/blockchain     # executa
```

- `-S .` = pasta do código-fonte (onde está o CMakeLists.txt)
- `-B build` = pasta onde vão os arquivos gerados

## Resumo do CMakeLists.txt deste projeto

```cmake
cmake_minimum_required(VERSION 3.16)

project(blockchain
    VERSION 0.1.0
    LANGUAGES C
)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)   # banco de compilação para o clangd

add_executable(blockchain
    src/main.c
    src/block.c
)

find_package(OpenSSL REQUIRED)          # cria o alvo OpenSSL::Crypto

target_include_directories(blockchain PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(blockchain PRIVATE OpenSSL::Crypto)
```
