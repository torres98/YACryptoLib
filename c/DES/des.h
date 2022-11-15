#include <stdint.h>

uint8_t* encrypt_block(const uint8_t* plaintext_block, const uint8_t* key);
uint8_t* decrypt_block(const uint8_t* ciphertext_block, const uint8_t* key);