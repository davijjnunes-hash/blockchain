#include "blockchain.h"

#include <stdio.h>
#include <string.h>

int main(void){
    Block genesis = {0};
    genesis.index = 0;
    genesis.timestamp = time(NULL);
    strncpy(genesis.data, "Genesis Block", sizeof(genesis.data) - 1);

    block_hash(&genesis, genesis.hash);


    printf("Bloco #%u\n", genesis.index);
    printf("Data:         %s\n", genesis.data);
    printf("Hash anterior: %s\n", genesis.previous_hash);
    printf("Hash:          %s\n", genesis.hash);
    return 0;



}
