#include<stdio.h>
#include<string.h>
#include<openssl/evp.h>
#include<openssl/rand.h>

int encrypt(unsigned char key[32], unsigned char iv[16], unsigned char password[128]){
    
    RAND_bytes(iv,sizeof(iv));

    EVP_CIPHER_CTX *ctx;
    ctx= EVP_CIPHER_CTX_new();

    EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv);

    unsigned char cipher[128];
    int len, cipher_len;

    EVP_EncryptUpdate(
        ctx,
        cipher,
        &len,
        password,
        strlen((char*)password)
    );

    cipher_len= len;

    EVP_EncryptFinal_ex(ctx, cipher+len, &len);
    cipher_len+=len;

    EVP_CIPHER_free(ctx);

}