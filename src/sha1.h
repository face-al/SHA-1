#ifndef SHA1_H
#define SHA1_H

#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define SHA1_BLOCK_SIZE 64    // Block size in bytes 64*8 = 512
#define SHA1_DIGEST_SIZE 20   // Digest size in bytes 20*8 = 160

// SHA-1 context structure
typedef struct {
    uint8_t buffer[SHA1_BLOCK_SIZE];  // Current 512-bit block
    size_t data_in_buffer;            // Length of data in the buffer in bytes
    uint64_t total_length;            // Total message length in bits
    uint32_t h[5];                    // Intermediate hash state
} SHA1_CTX;

// Function prototypes
uint8_t *sha1_pad(SHA1_CTX *msg);

#endif // SHA1_H