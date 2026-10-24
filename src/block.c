#include "blockchain.h"

#include <openssl/sha.h>
#include <stdio.h>
#include <string.h>

void block_hash(const Block *block, char output[HASH_HEX]){
    unsigned char digest[HASH_SIZE];
    char buffer[1024];

    int len = snprintf(buffer, sizeof(buffer),
        "%u|%lld|%u|%s|%s|%llu",
        block->index,
        (long long) block->timestamp,
        block->difficulty,
        block->data,
        block->previous_hash,
        (unsigned long long)block->nonce);

    SHA256((const unsigned char *)buffer, (size_t)len, digest);

    for (int i = 0; i < HASH_SIZE; i++) {
        sprintf(output + (i * 2), "%02x", digest[i]);
    }
    output[HASH_SIZE * 2] = '\0';
}
