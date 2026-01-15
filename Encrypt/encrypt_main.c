#include<stdio.h>
#include<string.h>
#include "encrypt.h"
#include "../db.h"
#include "../CreateHash/createHash.h"
#include "../ValidateHash/validate_main.h"

//Master password is password2
//password to be stored is password

//THIS FUNCTION WILL BE CALLED BY add_cmd() in CLI.c
int encrypt_main(char *password, char *password2, char *tag){

    if(validate_main(password2)==1){
        printf("\nACCESS DENIED!!!\n\n");
        return 1;
    }

    //This is to store the master Password in 32Bytes.
    unsigned char key[32];
    memset(key, 0, 32);  

    unsigned char iv[16];

    //This is the password to store
    

    unsigned char salt[16];



    //Converting the masterPassword to a raw hash to use as key for encryption
    int rc= get_HashRaw(password2, key, salt, strlen(password2), sizeof(key), sizeof(salt));

    if(rc!=0){
        printf("\nError getting raw Hash\n\n");
        return 1;
        
    }

    

    unsigned char cipher[128];
    int cipher_len;
    int iv_len;
    int salt_len= 16;
    db_init();
    int res= encrypt(key, iv, password, cipher, &cipher_len, &iv_len);  //USE BRAINN!!! Passing the len variables by reference!!!

    if(res!=0){
        printf("\nError encrypting\n\n");
        return 1;
        
    }


    
    //This function is from db.c. This is to store the key and the iv in the DB
    rc= store_password(tag,cipher, iv,salt, cipher_len, iv_len, salt_len);  

    if(rc!=0){
        printf("\nTag \"%s\" exists. Use a new one\n\n", tag);
        return 1;
        
    }

    return 0;

}