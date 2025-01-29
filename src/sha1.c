#include "sha1.h"

uint8_t* sha1_pad(SHA1_CTX *msg) {
    size_t curr_pos = msg->data_in_buffer;
    uint64_t msg_length = msg->total_length;

    // Calculate padding length
    size_t new_len = curr_pos + 1; // Add 1 for the 0x80 byte
    while (new_len % 64 != 56) { // Need 56 bytes to leave room for 8-byte length
        new_len++;
    }
    size_t total_len = new_len + 8; // Add 8 for the length field

    // Allocate memory for the padded message
    uint8_t *padded_msg = calloc(total_len, sizeof(uint8_t));
    if (!padded_msg) {
        return NULL;
    }

    // Copy original message
    memcpy(padded_msg, msg->buffer, curr_pos);

    // Add the 0x80 byte
    padded_msg[curr_pos] = 0x80;

    // Add the length in bits as big-endian
    for (int i = 0; i < 8; i++) {
        padded_msg[total_len - 8 + i] = (msg_length >> (56 - 8 * i)) & 0xFF;
    }

    return padded_msg;
}


