//Add a getHash_raw() function that uses the salt stored in the passwords DB to get the raw hash. This is the get the 32B key to encrypt the passwords.
// Add a getHash_raw_customSalt() That gives Argon2 raw hash for the specified salt.
#include<openssl/rand.h>
#include<stdio.h>
#include<string.h>
#include<argon2.h>
#include<stdlib.h>




//Run this only once to get the initial Hash for the master password
int getHash_encoded(char *password, char *encoded_hash, size_t hashlen){
    unsigned char salt[16];
    RAND_bytes(salt,sizeof(salt));

    

    //Encoded Hash to store in the DB
    //USe verify to check user input password with the hash stored in the DB
    int res1= argon2id_hash_encoded(
        10,
        1<<16,
        1,
        password, strlen(password),
        salt, sizeof(salt),
        32,
        encoded_hash, hashlen  //This encoded has stores the salt in it to so, dont store the salt in the DB.
    );

    
    

    if(res1!= ARGON2_OK){
        return 1;
    }

    else{
        return 0;
    }

}


int get_HashRaw(char *password, unsigned char *rawHash, unsigned char *salt, size_t p_len, size_t hash_len, size_t s_len){
    RAND_bytes(salt, s_len);

    int res= argon2id_hash_raw(
        10,
        1<<16,
        1,
        password, p_len,
        salt, s_len,
        rawHash, s_len
    );

    if(res== ARGON2_OK){
        return 0;
    }

    return 1;



}

int get_HashRaw_customSalt(char *password, unsigned char *rawHash, unsigned char *salt, size_t p_len, size_t hash_len, size_t s_len){
    
    int res= argon2id_hash_raw(
        10,
        1<<16,
        1,
        password, p_len,
        salt, s_len,
        rawHash, s_len
    );

    if(res== ARGON2_OK){
        return 0;
    }

    return 1;



}


