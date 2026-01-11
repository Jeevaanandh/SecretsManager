#include<stdio.h>
#include<openssl/evp.h>
#include<string.h>


int decrypt_password(unsigned char *key, unsigned char *cipher, unsigned char *iv, unsigned char *plainText, int cipher_len, int *plain_len){

    EVP_CIPHER_CTX *ctx;
    ctx= EVP_CIPHER_CTX_new();

    if(EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv) !=1){
        printf("1 Failed\n");
        return 1;
    }

    int len;

    if(EVP_DecryptUpdate(ctx, plainText, &len, cipher, cipher_len) !=1){
        printf("2 Failed\n");
        return 1;
    }
    *plain_len=len;

    if(EVP_DecryptFinal_ex(ctx, plainText+len, &len) !=1){
        printf("3 Failed\n");
        return 1;

    }
    *plain_len+=len;

    EVP_CIPHER_CTX_free(ctx);
    return 0;

}