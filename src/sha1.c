#include "sha1.h"

void sha1_pad(SHA1_CTX *msg) {
    size_t curr_pos = msg->data_in_buffer; // Current position in the buffer
    uint64_t msg_length = msg->total_length; // Original message length in bits

    // Part 1: Append 0x80
    msg->buffer[curr_pos++] = 0x80;

    // Part 2: Pad with 0x00 until buffer length is 56 bytes

    while(curr_pos > 56){
        if(curr_pos < 64){
            msg->buffer[curr_pos++] = 0x00;
        }
        curr_pos = 0;
    }


    while (curr_pos < 56) {
        msg->buffer[curr_pos++] = 0x00;
    }

    // Part 3: Append original message length as a 64-bit big-endian integer
    for (int i = 7; i >= 0; i--) {
        msg->buffer[curr_pos++] = (msg_length >> (i * 8)) & 0xFF;
    }
}


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
