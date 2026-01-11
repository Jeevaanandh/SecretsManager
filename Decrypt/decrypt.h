#ifndef DECRYPT_H
#define DECRYPT_H

int decrypt_password(unsigned char *key, unsigned char *cipher, unsigned char *iv, unsigned char *plainText, int cipher_len, int *plain_len);

#endif