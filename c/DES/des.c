#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "include/des.h"

#define BLOCK_SIZE 8

const uint8_t IP[] = {
    57, 49, 41, 33, 25, 17, 9, 1,
    59, 51, 43, 35, 27, 19, 11, 3,
    61, 53, 45, 37, 29, 21, 13, 5,
    63, 55, 47, 39, 31, 23, 15, 7,
    56, 48, 40, 32, 24, 16, 8, 0,
    58, 50, 42, 34, 26, 18, 10, 2,
    60, 52, 44, 36, 28, 20, 12, 4,
    62, 54, 46, 38, 30, 22, 14, 6
};


void permutation_layer(uint8_t* block) {
    uint8_t temp_block[BLOCK_SIZE] = {0};

    // perform the permutation
    // tip: the byte index starts at the 8th byte and then goes back to the 1st
    for (int i = 0; i < 64; i++) {
        uint8_t byte_index = IP[i] >> 3; // divide that by 8
        uint8_t byte_offset = 0x7 ^ (IP[i] & 0x7); // mod by 8

        temp_block[i >> 3] |= ((block[byte_index] >> byte_offset) & 0x1) << (0x7 ^ (i & 0x7));
    }
    // tip: pre-compute those indices

    // 000 => 111
    // 010 => 101
    memcpy(block, temp_block, BLOCK_SIZE);
}

// second implementation with two nested for-loops