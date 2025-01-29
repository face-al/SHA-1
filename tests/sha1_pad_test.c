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

// Test case: Short message ("abc")
void test_sha1_pad_short_message() {
    printf("Test: Short message ('abc')\n");

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

// Main function to run the test cases
int main() {
    test_sha1_pad_short_message();
    return 0;
}
