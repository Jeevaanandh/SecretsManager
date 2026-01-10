#include<openssl/rand.h>
#include<stdio.h>
#include<string.h>
#include<argon2.h>
#include<stdlib.h>


//Run this only once to get the initial Hash for the master password
int getHash(char password[100], char encoded_hash[128], unsigned char raw_hash[32]){
    unsigned char salt[16];
    RAND_bytes(salt,sizeof(salt));

    

    //Encoded Hash to store in the DB
    //USe verify to check user input password with the hash stored in the DB
    int res1= argon2id_hash_encoded(
        10,
        1<<18,
        1,
        password, strlen(password),
        salt, sizeof(salt),
        32,
        encoded_hash, sizeof(encoded_hash)
    );

    //This is to get the RAW hash that is to be used for the AES Key.
    int res2= argon2id_hash_raw(
        10,
        1<<18,
        1,
        password, strlen(password),
        salt, sizeof(salt),
        raw_hash, sizeof(raw_hash)
    );

    if(res1!= ARGON2_OK && res2!= ARGON2_OK){
        return 1;
    }

    else{
        return 0;
    }
}
