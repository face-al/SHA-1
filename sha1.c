#include "sha1.h"

void sha1_pad(SHA1_CTX *msg){
    size_t curr_pos = msg->data_in_buffer; //this is the current position
    printf("Before: curr_pos = %zu, data_in_buffer = %zu\n", curr_pos, msg->data_in_buffer);
    msg->buffer[curr_pos++] = 0x80; // Append
    msg->data_in_buffer++;
    printf("After: curr_pos = %zu, data_in_buffer = %zu\n", curr_pos, msg->data_in_buffer);


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
    memcpy(test->buffer, "abc", 3);
    test->data_in_buffer = 3;            // Set the buffer length
    test->total_length = 3 * 8;      // Total length in bits

    // Call the padding function
    sha1_pad(test);

    // Free the allocated memory
    free(test);

    return 0;
}
