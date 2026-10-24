# BlockChain
## Conceito
- Uma blockchain é uma lista encadeada onde cada bloco guarda o **hash do bloco anterior**. Isso os "acorrenta": altere qualquer bit de um bloco antigo e o hash dele muda, invalidando todos os seguintes.
- Nosso bloco tera:<br>
    
| Campo         | Tipo       | Para quê                                             |
|---------------|------------|------------------------------------------------------|
| index         | uint32_t   | Posição do bloco na chain (0 = gênese)               |
| timestamp     | time_t     | Quando foi criado                                    |
| data[256]     | char[]     | O payload (depois virarão transações)                |
| previous_hash | char[65]   | Hash do bloco anterior — a corrente                  |
| nonce         | uint64_t   | Contador de mineração (Aula 3)                       |
| difficulty    | uint32_t   | Zeros exigidos no início do hash (Aula 3)            |
| hash          | char[65]   | O hash do bloco (64 hex chars + \0)                  |

## block hash
  - void block_hash(const Block *block, char output[HASH_HEX])
  - A função tem quatro responsabilidades: serializar -> hashear -> converter

  ### Assinatura
  - const Block *block - recebe **ponteiro** para não copiar ~570bytes da struct a cada chamada. O **const** é um contrato: "só leio, não altero
