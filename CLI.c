#include<stdio.h>
#include<getopt.h>
#include<string.h>
#include<termios.h>
#include<unistd.h>

#include "Encrypt/encrypt_main.h"
#include "Decrypt/decrypt_main.h"
#include "ValidateHash/validate_main.h"
#include "CreateHash/hash_main.h"
#include "db.h"

void add_cmd(int argc, char *argv[]); //THIS IS TO ADD A NEW TAG:PASSWORD
void get_cmd(int argc, char *argv[]); //THIS IS TO FETCH A PASSWORD BASED ON THE TAG
void get_all(); //THIS IS TO GET ALL THE TAGS STORED
void delete_cmd(int argc, char *argv[]);

void disable_echo(){
    struct termios t;
    tcgetattr(STDIN_FILENO, &t);
    t.c_lflag &= ~ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &t);
}

void enable_echo(){
    struct termios t;
    tcgetattr(STDIN_FILENO, &t);
    t.c_lflag |= ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &t);
}

//USE THIS FUNCTION TO CHECK IF secrets.db EXISTS. OTHERWISE, THE USER NEEDS TO CREATE A MASTER KEY!!!
__attribute__((constructor))
void before_main() {
    int rc= check_init();

    printf("Runs First!!!\n");
    if(rc!=0){
        printf("\nRunning for the first time...\n");
        printf("\nInitializing...\n\n");

        db_init();

        char masterKey[128];
        printf("Create a Master Key: ");
        disable_echo();
        scanf("%s", masterKey);
        enable_echo();

        rc= hash_main(masterKey);

        if(rc==0){
            printf("\n\nMaster key saved successfully\n\n");
        }



    }
    
}


int main(int argc, char *argv[]){
    if(argc<2){
        printf("Help\n");
        return 1;
    }

    char command[100];
    strcpy(command, argv[1]);

    

    if(strcmp(command, "add")==0){
        add_cmd(argc-1, argv+1);
    }

    else if(strcmp(command, "get")==0){
        get_cmd(argc-1, argv+1);

    }

    else if(strcmp(command,"getall")==0){
        get_all();
    }

    else if(strcmp(command, "delete") == 0){
        delete_cmd(argc-1, argv+1);
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
    char masterKey[128];

    printf("Master Key: ");
    disable_echo();

    scanf("%s", masterKey);
    enable_echo();
    printf("\n");
    

    while((opt= getopt(argc, argv, "t:p:")) !=-1){
        switch(opt){
            case 't':
                strcpy(tag,optarg);
                break;

            case 'p':
                strcpy(password,optarg);
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
        
        int rc= encrypt_main(password, masterKey, tag);

        if(rc==0){
            printf("\nAdded Successfully\n\n");
        }

    }

}


void get_cmd(int argc, char *argv[]){

    int opt;
    char tag[100]= {'\0'};
    char masterKey[128];

    printf("Master Key: ");
    disable_echo();
    scanf("%s", masterKey);
    enable_echo();

    printf("\n");

    while((opt= getopt(argc, argv, "t:")) !=-1){
        switch(opt){
            case 't':
                strcpy(tag,optarg);
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

void get_all(){
    db_init();
    getTagsAll();

}

void delete_cmd(int argc, char *argv[]){
    int opt;
    char tag[100]= {'\0'};

    char masterKey[128];

    printf("Master Key: ");
    disable_echo();
    scanf("%s", masterKey);
    enable_echo();

    while((opt= getopt(argc, argv, "t:")) !=-1){
        switch(opt){
            case 't':
                strcpy(tag,optarg);
                break;


            default:
                printf("Error\n");
                return;

        }

    }

    if(tag[0]=='\0'){
        printf("Not Enough Arguments\n");
        printf("Help\n");
            
    }

    else{
        if(validate_main(masterKey)==0){
            int rc=delete_entry(tag);

            if(rc==0){

                printf("\n\nSuccessfully Deleted\n\n");
            }
            
        } 
        
        
        
    }

}