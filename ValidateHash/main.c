#include<stdio.h>
#include<string.h>
#include "validateHash.h"
#include "../db.h"

int main(int argc, char *argv[]){

    char password[128];
    strncpy(password, argv[1], sizeof(password)-1);
    password[sizeof(password)-1] = '\0';

    char encoded_hash[256];

    db_init();
    
    //Get the encoded hash first
    int rc= get_hash_fromDB(encoded_hash, sizeof(encoded_hash));

    if(rc==1){
        printf("Error\n");
    }

    rc= verifyPassword(password, encoded_hash);

    if(rc==0){
        printf("Password verified\n");
    }

    else{
        printf("Access Denied\n");
    }





    


}
