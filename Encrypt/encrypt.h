#ifndef ENCRYPT_H
#define ENCRYPT_H
int encrypt(unsigned char *key, unsigned char *iv, unsigned char *password,unsigned char *cipher, int *cipher_len, int *iv_len);
#endif