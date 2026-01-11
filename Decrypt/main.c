#include<stdio.h>
#include "decrypt.h"
#include "../db.h"
#include "../ValidateHash/validateHash.h"
#include<string.h>

int main(int argc, char *argv[]){

    char tag[100];
    strncpy(tag, argv[1], sizeof(tag)-1);
    tag[sizeof(tag)-1] = '\0';
    
    char password[128];
    strncpy(password, argv[2], sizeof(password) - 1);
    password[sizeof(password) - 1] = '\0';

    /* Use password as AES key (padded / truncated to 32 bytes) */
    unsigned char key[32];
    memset(key, 0, 32);
    memcpy(key, password, strlen(password) > 32 ? 32 : strlen(password));

    

    db_init();
    

    char encoded_hash[256];
    get_hash_fromDB(encoded_hash, sizeof(encoded_hash));

    unsigned char cipher[128];
    int cipher_len;
    unsigned char iv[16];
    int iv_len;

    unsigned char plainText[256];
    int plain_len;

    char finalTag[100];
    int rc= get_cipher_fromDB(tag, finalTag, cipher, iv, sizeof(tag), &cipher_len, &iv_len);

    if(rc==1){
        printf("Error\n");
        return 1;
    }

    rc= verifyPassword(password, encoded_hash);

    if(rc==0){
        rc= decrypt_password(key, cipher, iv, plainText, cipher_len, &plain_len);

        if(rc==0){
            printf("%s\n", plainText);
        }

        else{
            printf("Error2\n");
        }

    }

    else{
        printf("Access Denied\n");
    }


}