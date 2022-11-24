#include <stdint.h>


void encrypt_block(const uint8_t* plaintext_block, const uint8_t* key, uint8_t* ciphertext_block_buffer);

void decrypt_block(const uint8_t* ciphertext_block, const uint8_t* key, uint8_t* plaintext_block_buffer);
