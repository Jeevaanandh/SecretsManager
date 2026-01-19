#include<stdio.h>
#include<string.h>
#include "createHash.h"
#include "../db.h"

int hash_main(char *password){
    
    char encoded_hash[256];

    int rc= getHash_encoded(password, encoded_hash, sizeof(encoded_hash));

    if(rc==0){
        printf("Hash created successfully\n");
    }

    else{
        printf("Error\n");
    }

    db_init();

    //Call the function to store the encoded hash in the DB.

    rc= storeHash(encoded_hash);

    if(rc==0){
        return 0;
        printf("Hash stored successfully\n");
    }

    printf("%d\n", rc);

    return 1;



}