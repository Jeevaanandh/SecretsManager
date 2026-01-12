#ifndef HASH1
#define HASH1
#include <stddef.h>
int getHash_encoded(char *password, char *encoded_hash, size_t hashlen);
int get_HashRaw(char *password, unsigned char *rawHash, unsigned char *salt, size_t p_len, size_t hash_len, size_t s_len);
int get_HashRaw_customSalt(char *password, unsigned char *rawHash, unsigned char *salt, size_t p_len, size_t hash_len, size_t s_len);
#endif