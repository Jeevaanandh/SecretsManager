#include<stdio.h>
#include<string.h>
#include "validateHash.h"
#include "../db.h"

int validate_main(char *password){

    

    char encoded_hash[256];

    db_init();
    
    //Get the encoded hash first
    int rc= get_hash_fromDB(encoded_hash, sizeof(encoded_hash));

    if(rc==1){
        printf("Error\n");
    }

    rc= verifyPassword(password, encoded_hash);

    if(rc==0){
        return 0;
    }

    else{
        return 1;
        printf("Access Denied\n");
    }





    


}
