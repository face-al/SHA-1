#include "sha1.h"

void sha1_pad(SHA1_CTX *msg){
    size_t curr_pos = msg->data_in_buffer; //this is the current position
    uint64_t msg_length = msg->total_length; // message length initialy

    // Part 1 
    // Just add a one 1 and followed by 7 0's
    msg->buffer[curr_pos++] = 0x80; // Append
    msg->data_in_buffer++;

    // Part 2
    // We need to loop and add 0's until we reach 448 bits or 56 bytes
    while(curr_pos < 56){
        msg->buffer[curr_pos++] = 0x00;
        msg-> data_in_buffer++;
    }


    // Part 3
    // if original msg_length < 32 bits -> add 0 and then msg_length
    if(msg_length < 32){
        msg->buffer[curr_pos++] = 0x00;
        msg-> data_in_buffer++;
        msg->buffer[curr_pos++] = msg_length;
        msg-> data_in_buffer++;

    } else if(msg_length < 64){
        msg->buffer[curr_pos++] = msg_length;
        msg-> data_in_buffer++;
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
    memcpy(test->buffer, "abc", 3); // "abc" is 3 bytes
    test->data_in_buffer = 3;            // Set the buffer length
    test->total_length = 3 * 8;      // Total length in bits

    // Call the padding function
    sha1_pad(test);

    // Free the allocated memory
    free(test);

    return 0;
}
