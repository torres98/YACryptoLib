#include <assert.h>
#include <stdio.h>

#include "des.c"


int main() {
    // Initial Permutation Layer
    uint8_t init_perm_test_1[] = {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xff};
    const uint8_t init_perm_result_1[] = {0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80};
    initial_permutation(init_perm_test_1);
    assert(memcmp(init_perm_test_1, init_perm_result_1, BLOCK_SIZE) == 0);

    uint8_t init_perm_test_2[] = {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xff, 0x0};
    const uint8_t init_perm_result_2[] = {0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40};
    initial_permutation(init_perm_test_2);
    assert(memcmp(init_perm_test_2, init_perm_result_2, BLOCK_SIZE) == 0);

    uint8_t init_perm_test_3[] = {0xff, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xff};
    const uint8_t init_perm_result_3[] = {0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81};
    initial_permutation(init_perm_test_3);
    assert(memcmp(init_perm_test_3, init_perm_result_3, BLOCK_SIZE) == 0);


    uint8_t perm_test_2[BLOCK_SIZE] = {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xff, 0x0};
    const uint8_t perm_result_2[BLOCK_SIZE] = {0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40};
    initial_permutation(perm_test_2);
    assert(memcmp(perm_test_2, perm_result_2, BLOCK_SIZE) == 0);

    uint8_t perm_test_3[BLOCK_SIZE] = {0xff, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xff};
    const uint8_t perm_result_3[BLOCK_SIZE] = {0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81};
    initial_permutation(perm_test_3);
    assert(memcmp(perm_test_3, perm_result_3, BLOCK_SIZE) == 0);

    // Inverse Permutation Layer
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