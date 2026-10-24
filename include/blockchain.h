#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include <stdint.h>
#include <stddef.h>
#include <time.h>

#define HASH_SIZE 32
#define HASH_HEX (HASH_SIZE * 2  + 1)

typedef struct{
    uint32_t index;
    time_t timestamp;
    uint32_t difficulty;
    char data[256];
    char previous_hash[HASH_HEX];
    uint64_t nonce;
    char hash[HASH_HEX];
} Block;

void block_hash(const Block *block, char output[HASH_HEX]);

#endif
