#include<stdio.h>
#include<string.h>
#include<openssl/evp.h>
#include<openssl/rand.h>

int encrypt(unsigned char *key, unsigned char *iv, unsigned char *password,unsigned char *cipher, int *cipher_len, int *iv_len){
    
    RAND_bytes(iv,sizeof(iv));
    *iv_len= 16;

    EVP_CIPHER_CTX *ctx;
    ctx= EVP_CIPHER_CTX_new();

    EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv);

    
    int len;

    EVP_EncryptUpdate(
        ctx,
        cipher,
        &len,
        password,
        strlen((char*)password)
    );

    *cipher_len= len;

    EVP_EncryptFinal_ex(ctx, cipher+len, &len);
    *cipher_len+=len;

    EVP_CIPHER_CTX_free(ctx);

    return 0;

}