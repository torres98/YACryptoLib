#include <assert.h>
#include <stdio.h>

#include "des.c"


int main() {
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
    const uint8_t exp_expected_result_1[] = {0x20, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1f, 0x3e};
    expansion(exp_input_1, exp_result);
    assert(memcmp(exp_result, exp_expected_result_1, BLOCK_SIZE / 2) == 0);

    uint8_t exp_input_2[] = {0xff, 0x0, 0x0, 0x0};
    const uint8_t exp_expected_result_2[] = {0x1f, 0x3e, 0x20, 0x0, 0x0, 0x0, 0x0, 0x1};
    expansion(exp_input_2, exp_result);
    assert(memcmp(exp_result, exp_expected_result_2, BLOCK_SIZE / 2) == 0);

    uint8_t exp_input_3[] = {0xff, 0xff, 0xff, 0xff};
    const uint8_t exp_result_3[] = {0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f};
    expansion(exp_input_3, exp_result);
    assert(memcmp(exp_result, exp_result_3, BLOCK_SIZE / 2) == 0);

    
    // Substitution Layer
    uint8_t sub_result[8];

    const uint8_t sub_input_1[] = {0x18, 0x11, 0x1e, 0x3a, 0x21, 0x26, 0x14, 0x27};
    uint8_t sub_expected_result_1[] = {0x5, 0xc, 0x8, 0x2, 0xb, 0x5, 0x9, 0x7};
    substitution_layer(sub_input_1, sub_result);
    assert(memcmp(sub_result, sub_expected_result_1, BLOCK_SIZE) == 0);

    const uint8_t sub_input_2[] = {0x20, 0x32, 0x37, 0x1e, 0x1c, 0x0, 0x1, 0x1a};
    uint8_t sub_expected_result_2[] = {0x4, 0x8, 0x3, 0xf, 0xe, 0xc, 0xd, 0x0};
    substitution_layer(sub_input_2, sub_result);
    assert(memcmp(sub_result, sub_expected_result_2, BLOCK_SIZE) == 0);


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


    return 0;
}