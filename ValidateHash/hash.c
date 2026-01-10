#include<openssl/rand.h>
#include<stdio.h>
#include<string.h>
#include<argon2.h>
#include<stdlib.h>


//This function verifies the password witht the stored encoded hash.
int verifyPassword(char password[100], unsigned char encoded_hash[128]){
    int res= argon2_verify(encoded_hash, password, strlen(password), NULL);

    if(res!= ARGON2_OK){
        return 1;
    }

    else{
        return 0;
    }

}