#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "include/des.h"
#include "constants.h"

#define BLOCK_SIZE 8


const uint8_t IP_inverse[] = {
    39, 7, 47, 15, 55, 23, 63, 31,
    38, 6, 46, 14, 54, 22, 62, 30,
    37, 5, 45, 13, 53, 21, 61, 29,
    36, 4, 44, 12, 52, 20, 60, 28,
    35, 3, 43, 11, 51, 19, 59, 27,
    34, 2, 42, 10, 50, 18, 58, 26,
    33, 1, 41, 9, 49, 17, 57, 25,
    32, 0, 40, 8, 48, 16, 56, 24
};



void initial_permutation(uint8_t* block) {
    uint8_t temp_block[BLOCK_SIZE] = {0};

    for (int i = 0; i < BLOCK_SIZE; i++) {
        uint8_t bit_offset = H[i];

        for (int j = BLOCK_SIZE - 1; j >= 0; j--)
            temp_block[i] |= ((block[j] >> bit_offset) & 0x1) << j;
    }

    memcpy(block, temp_block, BLOCK_SIZE);
}

void expansion(uint8_t* right_block, uint8_t* out_block) {
    int input_bit_position = 31;

    for (int i = 0; i < BLOCK_SIZE; i++) {
        uint8_t output_byte = 0;

        for (int j = 5; j >= 0; j--) {
            int byte_index = input_bit_position >> 3;
            int bit_offset = 0x7 ^ (input_bit_position & 0x7);

            output_byte |= ((right_block[byte_index] >> bit_offset) & 0x1) << j;
            input_bit_position = (input_bit_position + 1) & 0x1f;
        }

        out_block[i] = output_byte;
        input_bit_position -= 2;
    }
}

void substitution_layer(uint8_t* block) {
    for (int i = 0; i < 8; i++) {
        int row_index = ((block[i] & 0x20) >> 4) | (block[i] & 0x1);
        int column_index = (block[i] & 0x1e) >> 1;

        block[i] = S[i][row_index][column_index];
    }
}

void permutation_layer(uint8_t* block) {
    uint8_t temp_block[BLOCK_SIZE] = {0};

    for (int i = 0; i < 32; i++) {
        uint8_t byte_index = P[i] >> 2;
        uint8_t byte_offset = 0x3 ^ (P[i] & 0x3);

        temp_block[i >> 2] |= ((block[byte_index] >> byte_offset) & 0x1) << (0x3 ^ (i & 0x3));
    }

    memcpy(block, temp_block, BLOCK_SIZE);
}

void cipher_function(uint8_t* right_block, const uint8_t* round_key) {
    uint8_t temp_block[BLOCK_SIZE] = {0};

    expansion(right_block, temp_block);

    // XOR with round key
    for (int i = 0; i < 8; i++)
        temp_block[i] ^= round_key[i];

    substitution_layer(temp_block);
    permutation_layer(temp_block);

    // dump the result in the right_block array
    for (int i = 0; i < 4; i++)
        right_block[i] = (temp_block[2*i] << 4) | temp_block[2*i+1];
}

void inverse_initial_permutation(uint8_t* block) {
    uint8_t temp_block[BLOCK_SIZE] = {0};

    // perform the permutation
    // tip: the byte index starts at the 8th byte and then goes back to the 1st
    for (int i = 0; i < 64; i++) {
        uint8_t byte_index = IP_inverse[i] >> 3; // divide that by 8
        uint8_t byte_offset = 0x7 ^ (IP_inverse[i] & 0x7); // mod by 8

        temp_block[i >> 3] |= ((block[byte_index] >> byte_offset) & 0x1) << (0x7 ^ (i & 0x7));
    }
    // tip: pre-compute those indices

    // 000 => 111
    // 010 => 101
    memcpy(block, temp_block, BLOCK_SIZE);
}