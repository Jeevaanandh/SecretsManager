#include<stdio.h>
#include "decrypt.h"
#include "../db.h"
#include "../ValidateHash/validateHash.h"
#include "../CreateHash/createHash.h"
#include<string.h>

int decrypt_main(char *tag, char *password){

    
    
    

    /* Use password as AES key */
    unsigned char key[32];
    memset(key, 0, sizeof(key)); 
    

    

    db_init();
    

    char encoded_hash[256];
    get_hash_fromDB(encoded_hash, sizeof(encoded_hash));

    unsigned char cipher[128];
    int cipher_len;
    unsigned char iv[16];
    int iv_len;
    unsigned char salt[16];
    int salt_len;

    unsigned char plainText[256];
    int plain_len;

    char finalTag[100];
    int rc= get_cipher_fromDB(tag, finalTag, cipher, iv,salt, sizeof(tag), &cipher_len, &iv_len, &salt_len);

    if(rc==1){
        printf("Error\n");
        return 1;
    }

    rc= get_HashRaw_customSalt(password, key, salt, strlen(password), sizeof(key), salt_len);



    if(rc==1){
        printf("Error in getting Raw Hash\n");
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
            return 1;
        }

    }

    else{
        printf("Access Denied\n");
        return 1;
    }


    return 0;


}