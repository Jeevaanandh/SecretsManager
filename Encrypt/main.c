#include<stdio.h>
#include<string.h>
#include "encrypt.h"
#include "../db.h"

int main(int argc, char *argv[]){
    unsigned char key[32];
    memset(key, 0, 32);  

    unsigned char iv[16];
    unsigned char password[128]; //This is given by the user, soooo assign this to one of the argv ‼️ (DONE)
    char tag[100];

    strncpy((char*)password, argv[1], sizeof(password)-1);
    strncpy((char*)tag, argv[2], sizeof(tag)-1);
    password[sizeof(password)-1] = '\0';

    unsigned char cipher[128];
    int cipher_len;
    int iv_len;
    db_init();
    int res= encrypt(key, iv, password, cipher, &cipher_len, &iv_len);  //USE BRAINN!!! Passing the len variables by reference!!!

    
    //This function is from db.c. This is to store the key and the iv in the DB
    store_password(tag,cipher, iv, cipher_len, iv_len);  

}