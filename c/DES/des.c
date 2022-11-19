#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "include/des.h"
#include "constants.h"

#define BLOCK_SIZE 8


// Key-related operations

void permute_key(const uint8_t* key, uint8_t* out_key) {
    int table_index = 0;

    for (int i = 0; i < BLOCK_SIZE; i++) {
        uint8_t output_byte = 0;

        for (int j = 6; j >= 0; j--) {
            uint8_t byte_index = PC1[table_index] >> 3;
            uint8_t bit_offset = 0x7 ^ (PC1[table_index++] & 0x7);

            output_byte |= ((key[byte_index] >> bit_offset) & 0x1) << j;
        }

        out_key[i] = output_byte;
    }
}

void rotate_state(uint8_t* state, unsigned nround) {
    uint8_t carry_over = 0;

    if (nround == 1 || nround == 2 || nround == 9 || nround == 16) {
        for (int i = 3; i >= 0; i--) {
            state[i] = (state[i] << 1) | carry_over;
            carry_over = state[i] >> 7;

            state[i] &= 0x7f;
        }
        
        state[3] |= carry_over;

        carry_over = 0;

        for (int i = 7; i >= 4; i--) {
            state[i] = (state[i] << 1) | carry_over;
            carry_over = state[i] >> 7;

            state[i] &= 0x7f;
        }

        state[7] |= carry_over;

    } else {
        for (int i = 3; i >= 0; i--) {
            uint8_t carry_over_temp = (state[i] >> 5) & 0x3;
            state[i] = (state[i] << 2) | carry_over;
            carry_over = carry_over_temp;

            state[i] &= 0x7f;
        }
        
        state[3] |= carry_over;

        carry_over = 0;

        for (int i = 7; i >= 4; i--) {
            uint8_t carry_over_temp = (state[i] >> 5) & 0x3;
            state[i] = (state[i] << 2) | carry_over;
            carry_over = carry_over_temp;

            state[i] &= 0x7f;
        }

        state[7] |= carry_over;
    }
}

void get_round_key(const uint8_t *state, uint8_t *round_key_buffer) {
    int table_index = 0;

    for (int i = 0; i < BLOCK_SIZE; i++) {
        uint8_t round_key_byte = 0;

        for (int j = 5; j >= 0; j--) {
            uint8_t byte_index = PC2[table_index] / 7;
            uint8_t bit_offset = 6 - (PC2[table_index++] % 7);

            round_key_byte |= ((state[byte_index] >> bit_offset) & 0x1) << j;
        }

        round_key_buffer[i] = round_key_byte;
    }
}


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