#include <sha1.h>

int main() {
    // Dynamically allocate memory for the SHA-1 context
    SHA1_CTX *test = malloc(sizeof(SHA1_CTX));
    if (test == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;  // Exit with an error code
    }

    // Initialize all fields to 0
    memset(test, 0, sizeof(SHA1_CTX));

    // Copy the message "abc" into the buffer
    memcpy(test->buffer, "abcabcababcabcababcabcababcabcababcabcababcabcababcabcababcabcab987", 67); // "abc" is 3 bytes
    test->data_in_buffer = 67;            // Set the buffer length
    test->total_length = 67 * 8;      // Total length in bits

    // Call the padding function
    sha1_pad(test);

   
     // Print the padded buffer
    printf("Padded buffer:\n");
    for (size_t i = 0; i < 67; i++) {
        printf("%02x ", test->buffer[i]);
        if ((i + 1) % 16 == 0) printf("\n"); // Print 16 bytes per line
    }

     // Free the allocated memory
    free(test);

    return 0;
}