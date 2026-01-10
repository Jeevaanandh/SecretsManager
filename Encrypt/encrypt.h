#ifndef ENCRYPT_H
#define ENCRYPT_H
int encrypt(unsigned char key[32], unsigned char iv[16], unsigned char password[128],unsigned char cipher[128], int *cipher_len, int *iv_len);

#endif