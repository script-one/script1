#include "sha256.h"
#include <time.h>
#define u64 unsigned long long

int leadzero(BYTE *b, int max_len) {
    int lead = 0;
    int i;
    for (i=0; i<max_len; i++) {
        if (b[i] == 0) lead += 8; else break;
    }
    if (i==max_len) return lead;
    int size = sizeof(BYTE)*8;
    BYTE msb = 1<<(size-1);
    for(int bit = 0; bit < size; bit++){
        if((b[i] << bit) & msb) {
            break;
        }
        lead++;
    }
    return lead;
}

u64 mining(BYTE *block, int block_len, BYTE *hash, int zeros, int max_loop) {
    for (int t=0; t<max_loop; t++) {
        u64 nonce;
        BYTE *p = (BYTE*) &nonce;
        for (int i=0; i<sizeof(nonce); i++) {
            p[i] = rand() % 255;
        }
        SHA256_CTX ctx;
        sha256_init(&ctx);
        sha256_update(&ctx, (BYTE*) &nonce, sizeof(nonce));
        sha256_update(&ctx, block, block_len);
        sha256_final(&ctx, hash);
        int leads = leadzero(hash, SHA256_BLOCK_SIZE);
        // hex_print(hash, SHA256_BLOCK_SIZE);
        // printf(" leads=%d\n", leads);
        if (leads >= zeros) return nonce;
    }
    return -1;
}

int main()
{
    // BYTE b[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x8F };
    // BYTE b[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
    // printf("leadzero()=%d\n", leadzero(b, 9)); // should be 8*5+4 = 44

    srand(time(NULL));
	char block[] = "john=>george $20, john=>mary $10";
    BYTE hash[SHA256_BLOCK_SIZE];
    int zeros = 21;
    u64 nonce = mining((BYTE*) block, strlen(block), hash, zeros, 99999999);
    hex_print(hash, SHA256_BLOCK_SIZE);
    printf("\nnonce=%lu\n", (long unsigned int) nonce);
	return(0);
}
