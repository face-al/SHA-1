#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../src/sha1.h"

// Helper function to print a buffer in hex
void print_hex(const uint8_t *buffer, size_t length) {
    for (size_t i = 0; i < length; i++) {
        printf("%02x ", buffer[i]);
        if ((i + 1) % 16 == 0) printf("\n");
    }
    printf("\n");
}

// Test case 1
void test1_sha1_pad() {
    printf("Test message: 'abc'\n");

    SHA1_CTX ctx;
    memset(&ctx, 0, sizeof(SHA1_CTX));

    // Input: "abc"
    const char *message = "abc";
    memcpy(ctx.buffer, message, strlen(message));
    ctx.data_in_buffer = strlen(message);
    ctx.total_length = strlen(message) * 8; // Length in bits

    // Call sha1_pad
    uint8_t *padded_msg = sha1_pad(&ctx);

    if (!padded_msg) {
        printf("Error: sha1_pad returned NULL\n");
        return;
    }

    // Expected padded output for "abc"
    uint8_t expected[64] = {
        0x61, 0x62, 0x63, 0x80, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18
    };

    size_t expected_len = 64; // Length of the expected output


    // Compare the padded output to the expected result
    int passed = 1;
    for (size_t i = 0; i < expected_len; i++) {
        if (padded_msg[i] != expected[i]) {
            printf("Mismatch at byte %zu: expected %02x, got %02x\n",
                   i, expected[i], padded_msg[i]);
            passed = 0;
        }
    }

    if (passed) {
        printf("Test passed!\n");
    } else {
        printf("Test failed.\n");
    }

    // Free the allocated memory
    free(padded_msg);
}

// Test case 2
void test2_sha1_pad() {
    printf("Test message: 'CRC is the best center at TII'\n");

    SHA1_CTX ctx;
    memset(&ctx, 0, sizeof(SHA1_CTX));

    // Input: "abc"
    const char *message = "CRC is the best center at TII";
    memcpy(ctx.buffer, message, strlen(message));
    ctx.data_in_buffer = strlen(message);
    ctx.total_length = strlen(message) * 8; // Length in bits

    // Call sha1_pad
    uint8_t *padded_msg = sha1_pad(&ctx);

    if (!padded_msg) {
        printf("Error: sha1_pad returned NULL\n");
        return;
    }

    // Expected padded output for "abc"
    uint8_t expected[64] = {
            0x43, 0x52, 0x43, 0x20, 0x69, 0x73, 0x20, 0x74,
            0x68, 0x65, 0x20, 0x62, 0x65, 0x73, 0x74, 0x20,
            0x63, 0x65, 0x6e, 0x74, 0x65, 0x72, 0x20, 0x61,
            0x74, 0x20, 0x54, 0x49, 0x49, 0x80, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe8
    };

    size_t expected_len = 64; // Length of the expected output

    // Compare the padded output to the expected result
    int passed = 1;
    for(size_t i = 0; i < expected_len; i++) {
        if (padded_msg[i] != expected[i]) {
            printf("Mismatch at byte %zu: expected %02x, got %02x\n",
                   i, expected[i], padded_msg[i]);
            passed = 0;
        }
    }

    if (passed) {
        printf("Test passed!\n");
    } else {
        printf("Test failed.\n");
    }

    // print_hex(padded_msg, expected_len);

    // Free the allocated memory
    free(padded_msg);
}


// Test case 3 - Edge case where the text is longer than 512 bits
void test3_sha1_pad() {
    printf("Test message: '65 a's'\n");

    SHA1_CTX ctx;
    memset(&ctx, 0, sizeof(SHA1_CTX));

    // Input: "abc"
    const char *message = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
    memcpy(ctx.buffer, message, strlen(message));
    ctx.data_in_buffer = strlen(message);
    ctx.total_length = strlen(message) * 8; // Length in bits

    // Call sha1_pad
    uint8_t *padded_msg = sha1_pad(&ctx);

    if (!padded_msg) {
        printf("Error: sha1_pad returned NULL\n");
        return;
    }

    // Expected padded output for "65 a's"
    uint8_t expected[128] = {
        0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61,
        0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61,
        0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61,
        0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61,
        0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61,
        0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61,
        0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61,
        0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61,
        0x61, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x08
    };

    size_t expected_len = 128; // Length of the expected output

    // Compare the padded output to the expected result
    int passed = 1;
    for(size_t i = 0; i < expected_len; i++) {
        if (padded_msg[i] != expected[i]) {
            printf("Mismatch at byte %zu: expected %02x, got %02x\n",
                   i, expected[i], padded_msg[i]);
            passed = 0;
        }
    }

    if (passed) {
        printf("Test passed!\n");
    } else {
        printf("Test failed.\n");
    }

    // print_hex(padded_msg, expected_len);

    // Free the allocated memory
    free(padded_msg);
}


// Main function to run the test cases
int main() {
    test1_sha1_pad();
    test2_sha1_pad();
    test3_sha1_pad();
    return 0;
}
