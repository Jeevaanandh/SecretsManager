#include<stdio.h>
#include<getopt.h>
#include<string.h>

#include "Encrypt/encrypt_main.h"
#include "Decrypt/decrypt_main.h"

void add_cmd(int argc, char *argv[]);
void get_cmd(int argc, char *argv[]);

int main(int argc, char *argv[]){
    if(argc<2){
        printf("Help\n");
        return 1;
    }

    char command[100];
    strcpy(command, argv[1]);

    printf("command: %s\n", command);

    if(strcmp(command, "add")==0){
        add_cmd(argc-1, argv+1);
    }

    else if(strcmp(command, "get")==0){
        get_cmd(argc-1, argv+1);

    }

    else{
        printf("Help\n");
        return 0;
    }

}


void add_cmd(int argc, char *argv[]){
    
    int opt;
    char tag[100]= {'\0'};
    char password[128]= {'\0'};
    char masterKey[128]= {'\0'};

    while((opt= getopt(argc, argv, "t:p:k:")) !=-1){
        switch(opt){
            case 't':
                strcpy(tag,optarg);
                break;

            case 'p':
                strcpy(password,optarg);
                break;

            case 'k':
                strcpy(masterKey, optarg);
                break;

            default:
                printf("Error\n");
                return;

        }

        
    }

    if(tag[0]=='\0' || password[0]=='\0' || masterKey[0]=='\0'){
        printf("Not Enough Arguments\n");
        printf("Help\n");
            
    }

    else{
        //Call encrypt
        printf("Calling the function\n");
        int rc= encrypt_main(password, masterKey, tag);

        if(rc==0){
            printf("Added Successfully\n");
        }

    }

}


void get_cmd(int argc, char *argv[]){

    int opt;
    char tag[100]= {'\0'};
    char masterKey[128]= {'\0'};

    while((opt= getopt(argc, argv, "t:k:")) !=-1){
        switch(opt){
            case 't':
                strcpy(tag,optarg);
                break;

            case 'k':
                strcpy(masterKey, optarg);
                break;

            default:
                printf("Error\n");
                return;

        }

    }

    if(tag[0]=='\0' || masterKey[0]=='\0'){
        printf("Not Enough Arguments\n");
        printf("Help\n");
            
    }

    else{
        decrypt_main(tag, masterKey);
    }



}   