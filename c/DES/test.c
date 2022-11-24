#include <assert.h>
#include <stdio.h>

#include "des.c"


int main() {

    // Permute Key
    uint8_t permuted_key[BLOCK_SIZE];

    const uint8_t permkey_input_1[] = {0x13, 0x34, 0x57, 0x79, 0x9b, 0xbc, 0xdf, 0xf1};
    const uint8_t permkey_expected_result_1[] = {0x78, 0x33, 0x15, 0x2f, 0x2a, 0x59, 0x4f, 0xf};
    permute_key(permkey_input_1, permuted_key);
    assert(memcmp(permuted_key, permkey_expected_result_1, BLOCK_SIZE) == 0);


    // Rotate State & Get Round Key
    uint8_t round_key[BLOCK_SIZE];
    uint8_t state_input[] = {0x78, 0x33, 0x15, 0x2f, 0x2a, 0x59, 0x4f, 0xf};
    
    const uint8_t rotstate_expected_output_1[] = {0x70, 0x66, 0x2a, 0x5f, 0x55, 0x33, 0x1e, 0x1e};
    const uint8_t rk_expected_output_1[] = {0x6, 0x30, 0xb, 0x2f, 0x3f, 0x7, 0x1, 0x32};
    left_rotate_key_state(state_input, 1);
    get_round_key(state_input, round_key);
    for (int i = 0; i < BLOCK_SIZE; i++) state_input[i] &= 0x7f;
    assert(memcmp(state_input, rotstate_expected_output_1, BLOCK_SIZE) == 0);
    assert(memcmp(round_key, rk_expected_output_1, BLOCK_SIZE) == 0);

    const uint8_t rotstate_expected_output_2[] = {0x61, 0x4c, 0x55, 0x3f, 0x2a, 0x66, 0x3c, 0x3d};
    const uint8_t rk_expected_output_2[] = {0x1e, 0x1a, 0x3b, 0x19, 0x36, 0x3c, 0x27, 0x25};
    left_rotate_key_state(state_input, 2);
    get_round_key(state_input, round_key);
    for (int i = 0; i < BLOCK_SIZE; i++) state_input[i] &= 0x7f;
    assert(memcmp(state_input, rotstate_expected_output_2, BLOCK_SIZE) == 0);
    assert(memcmp(round_key, rk_expected_output_2, BLOCK_SIZE) == 0);

    const uint8_t rotstate_expected_output_3[] = {0x6, 0x32, 0x55, 0x7f, 0x2b, 0x19, 0x71, 0x75};
    const uint8_t rk_expected_output_3[] = {0x15, 0x1f, 0x32, 0xa, 0x10, 0x2c, 0x3e, 0x19};
    left_rotate_key_state(state_input, 3);
    get_round_key(state_input, round_key);
    for (int i = 0; i < BLOCK_SIZE; i++) state_input[i] &= 0x7f;
    assert(memcmp(state_input, rotstate_expected_output_3, BLOCK_SIZE) == 0);
    assert(memcmp(round_key, rk_expected_output_3, BLOCK_SIZE) == 0);


    // Initial Permutation Layer
    uint8_t initperm_input_1[] = {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xff};
    const uint8_t initperm_expected_result_1[] = {0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80};
    initial_permutation(initperm_input_1);
    assert(memcmp(initperm_input_1, initperm_expected_result_1, BLOCK_SIZE) == 0);

    uint8_t initperm_input_2[] = {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xff, 0x0};
    const uint8_t initperm_expected_result_2[] = {0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40};
    initial_permutation(initperm_input_2);
    assert(memcmp(initperm_input_2, initperm_expected_result_2, BLOCK_SIZE) == 0);

    uint8_t initperm_input_3[] = {0xff, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xff};
    const uint8_t initperm_expected_result_3[] = {0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81};
    initial_permutation(initperm_input_3);
    assert(memcmp(initperm_input_3, initperm_expected_result_3, BLOCK_SIZE) == 0);


    // Expansion Layer
    uint8_t exp_result[BLOCK_SIZE];

    uint8_t exp_input_1[] = {0x0, 0x0, 0x0, 0xff};
    const uint8_t exp_expected_result_1[] = {0x20, 0x0, 0x0, 0x0, 0x0, 0x1, 0x1f, 0x3e};
    expansion(exp_input_1, exp_result);
    assert(memcmp(exp_result, exp_expected_result_1, BLOCK_SIZE) == 0);

    uint8_t exp_input_2[] = {0xff, 0x0, 0x0, 0x0};
    const uint8_t exp_expected_result_2[] = {0x1f, 0x3e, 0x20, 0x0, 0x0, 0x0, 0x0, 0x1};
    expansion(exp_input_2, exp_result);
    assert(memcmp(exp_result, exp_expected_result_2, BLOCK_SIZE) == 0);

    uint8_t exp_input_3[] = {0xff, 0xff, 0xff, 0xff};
    const uint8_t exp_result_3[] = {0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f};
    expansion(exp_input_3, exp_result);
    assert(memcmp(exp_result, exp_result_3, BLOCK_SIZE) == 0);

    
    // Substitution Layer
    uint8_t sub_input_1[] = {0x18, 0x11, 0x1e, 0x3a, 0x21, 0x26, 0x14, 0x27};
    uint8_t sub_expected_result_1[] = {0x5, 0xc, 0x8, 0x2, 0xb, 0x5, 0x9, 0x7};
    substitution_layer(sub_input_1);
    assert(memcmp(sub_input_1, sub_expected_result_1, BLOCK_SIZE) == 0);

    uint8_t sub_input_2[] = {0x20, 0x32, 0x37, 0x1e, 0x1c, 0x0, 0x1, 0x1a};
    uint8_t sub_expected_result_2[] = {0x4, 0x8, 0x3, 0xf, 0xe, 0xc, 0xd, 0x0};
    substitution_layer(sub_input_2);
    assert(memcmp(sub_input_2, sub_expected_result_2, BLOCK_SIZE) == 0);


    // Permutation Layer
    uint8_t perm_input_1[] = {0x5, 0xc, 0x8, 0x2, 0xb, 0x5, 0x9, 0x7};
    const uint8_t perm_expected_result_1[] = {0x2, 0x3, 0x4, 0xa, 0xa, 0x9, 0xb, 0xb};
    permutation_layer(perm_input_1);
    assert(memcmp(perm_input_1, perm_expected_result_1, BLOCK_SIZE) == 0);

    uint8_t perm_input_2[] = {0x4, 0x8, 0x3, 0xf, 0xe, 0xc, 0xd, 0x0};
    const uint8_t perm_expected_result_2[] = {0x9, 0x7, 0x5, 0xc, 0x9, 0x0, 0xc, 0xd};
    permutation_layer(perm_input_2);
    assert(memcmp(perm_input_2, perm_expected_result_2, BLOCK_SIZE) == 0);

    
    // Cipher Function Layer
    uint8_t f_input_1[] = {0xf0, 0xaa, 0xf0, 0xaa};
    const uint8_t f_key_1[] = {0x6, 0x30, 0xb, 0x2f, 0x3f, 0x7, 0x1, 0x32};
    const uint8_t f_expected_result_1[] = {0x23, 0x4a, 0xa9, 0xbb};
    cipher_function(f_input_1, f_key_1);
    assert(memcmp(f_input_1, f_expected_result_1, BLOCK_SIZE / 2) == 0);

    uint8_t f_input_2[] = {0x0, 0x7e, 0x80, 0xd};
    const uint8_t f_key_2[] = {0x0, 0x32, 0x38, 0x23, 0xc, 0x0, 0x0, 0x0};
    const uint8_t f_expected_result_2[] = {0x97, 0x5c, 0x90, 0xcd};
    cipher_function(f_input_2, f_key_2);
    assert(memcmp(f_input_2, f_expected_result_2, BLOCK_SIZE / 2) == 0);


    // Inverse Initial Permutation Layer
    uint8_t inv_perm_test_1[BLOCK_SIZE] = {0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80};
    const uint8_t inv_perm_result_1[BLOCK_SIZE] = {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xff};
    inverse_initial_permutation(inv_perm_test_1);
    assert(memcmp(inv_perm_test_1, inv_perm_result_1, BLOCK_SIZE) == 0);

    uint8_t inv_perm_test_2[BLOCK_SIZE] = {0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40};
    const uint8_t inv_perm_result_2[BLOCK_SIZE] = {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xff, 0x0};
    inverse_initial_permutation(inv_perm_test_2);
    assert(memcmp(inv_perm_test_2, inv_perm_result_2, BLOCK_SIZE) == 0);

    uint8_t inv_perm_test_3[BLOCK_SIZE] = {0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81};
    const uint8_t inv_perm_result_3[BLOCK_SIZE] = {0xff, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xff};
    inverse_initial_permutation(inv_perm_test_3);
    assert(memcmp(inv_perm_test_3, inv_perm_result_3, BLOCK_SIZE) == 0);


    // Block Encryption
    uint8_t encrypt_result[BLOCK_SIZE];

    const uint8_t encrypt_input_1[BLOCK_SIZE] = {0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef};
    const uint8_t encrypt_key_1[BLOCK_SIZE] = {0x13, 0x34, 0x57, 0x79, 0x9b, 0xbc, 0xdf, 0xf1};
    const uint8_t encrypt_expected_result_1[BLOCK_SIZE] = {0x85, 0xe8, 0x13, 0x54, 0x0f, 0x0a, 0xb4, 0x05};
    encrypt_block(encrypt_input_1, encrypt_key_1, encrypt_result);
    assert(memcmp(encrypt_result, encrypt_expected_result_1, BLOCK_SIZE) == 0);

    const uint8_t encrypt_input_2[BLOCK_SIZE] = {0x95, 0xf8, 0xa5, 0xe5, 0xdd, 0x31, 0xd9, 0x0};
    const uint8_t encrypt_key_2[BLOCK_SIZE] = {0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1};
    const uint8_t encrypt_expected_result_2[BLOCK_SIZE] = {0x80, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
    encrypt_block(encrypt_input_2, encrypt_key_2, encrypt_result);
    assert(memcmp(encrypt_result, encrypt_expected_result_2, BLOCK_SIZE) == 0);


    return 0;
}