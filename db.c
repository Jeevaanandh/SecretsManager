//Use Sqlite to Add to the DB.
//You have to add function to: Store Master Password Hash
//                             Store Encrypted password and IV (DONE)
//                             Retrieve the encoded hash of the mater password [This is for validateHash] (DONE)

#include<stdio.h>
#include<string.h>
#include "db.h"
#include<stdlib.h>



const char *sql;
int rc;
const char *homedir;

sqlite3 *DB= NULL;


int db_init(){
    char db_path[1024];
    #if defined(_WIN32) || defined(_WIN64)
        homedir= getenv("USERPROFILE");
        snprintf(db_path, sizeof(db_path), "%s\\secrets.db", homedir);

    

    #else
        homedir= getenv("HOME");
        snprintf(db_path, sizeof(db_path), "%s/secrets.db", homedir);

    #endif

    if(homedir == NULL){
        return 1;
    }

    
    
    

    if(sqlite3_open(db_path, &DB) != SQLITE_OK){
        return -1;
    }

    return 0;


}



int store_password(char *tag,unsigned char *cipher, unsigned char *iv, unsigned char *salt, int cipher_len, int iv_len, int salt_len){
    sql= "CREATE TABLE IF NOT EXISTS passwords2(tag TEXT PRIMARY KEY, cipher BLOB, iv BLOB, salt BLOB);";

    sqlite3_stmt *stmt;

    sqlite3_prepare_v2(DB, sql, -1, &stmt, NULL);
    rc= sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    if(rc!= SQLITE_DONE){
        return 1;
    }

    sql= "INSERT INTO passwords2 (tag,cipher,iv,salt) VALUES (?,?,?,?);";
    sqlite3_prepare_v2(DB, sql, -1, &stmt, NULL);

    sqlite3_bind_text(stmt, 1, tag, -1, SQLITE_TRANSIENT);
    sqlite3_bind_blob(stmt, 2, cipher, cipher_len, SQLITE_TRANSIENT);
    sqlite3_bind_blob(stmt, 3, iv, iv_len, SQLITE_TRANSIENT);
    sqlite3_bind_blob(stmt, 4, salt, salt_len, SQLITE_TRANSIENT);

    rc= sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    if(rc!= SQLITE_DONE){
        return 1;
    }

    return 0;

}


int storeHash(char *encoded_hash){
    sql= "CREATE TABLE IF NOT EXISTS MasterHash (hash TEXT);";

    sqlite3_stmt *stmt;

    sqlite3_prepare_v2(DB, sql, -1, &stmt, NULL);
    rc= sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    if(rc!= SQLITE_DONE){
        return 1;
    }

    sql= "INSERT INTO MasterHash (hash) VALUES (?);";
    sqlite3_prepare_v2(DB, sql, -1, &stmt, NULL);

    sqlite3_bind_text(stmt, 1, encoded_hash, -1, SQLITE_TRANSIENT);

    rc= sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    if(rc!= SQLITE_DONE){
        return 1;
    }

    return 0;

}


int get_hash_fromDB(char *encoded_hash, size_t hashlen){
    sql= "SELECT hash FROM MasterHash;";

    sqlite3_stmt *stmt;

    sqlite3_prepare_v2(DB, sql, -1, &stmt, NULL);
    
    if(sqlite3_step(stmt)== SQLITE_ROW){
        const char *db_text= (char *) sqlite3_column_text(stmt,0);

        strncpy(encoded_hash, db_text, hashlen-1);
        encoded_hash[hashlen-1]= '\0';

        sqlite3_finalize(stmt);

        return 0;
    }

    return -1;

}


int get_cipher_fromDB(char * tag, char *storeTag, unsigned char *cipher, unsigned char *iv, unsigned char *salt, size_t t_len, int *cipher_size, int *iv_size, int *salt_size){
    sql= "SELECT tag, cipher, iv, salt FROM passwords2 WHERE tag= ?;";

    
    sqlite3_stmt *stmt;

    sqlite3_prepare_v2(DB, sql, -1, &stmt, NULL);

    sqlite3_bind_text(stmt, 1, tag, -1, SQLITE_TRANSIENT);

    const char *t;
    const unsigned char *cblob;
    const unsigned char *iv_blob;
    const unsigned char *salt_blob;

    if(sqlite3_step(stmt)==SQLITE_ROW){
        t= (const char *) sqlite3_column_text(stmt,0);
        cblob= (const unsigned char *) sqlite3_column_blob(stmt,1);
        int csize= sqlite3_column_bytes(stmt,1);

        iv_blob= (const unsigned char *) sqlite3_column_blob(stmt,2);
        int isize= sqlite3_column_bytes(stmt,2);

        salt_blob= (const unsigned char *) sqlite3_column_blob(stmt,3);
        int ssize= sqlite3_column_bytes(stmt,3);

        strncpy(storeTag, t, t_len-1);
        storeTag[t_len-1]= '\0';

        memcpy(cipher, cblob, csize);
        memcpy(iv, iv_blob, isize);
        memcpy(salt, salt_blob, ssize);

        *cipher_size= csize;
        *iv_size= isize;
        *salt_size= ssize;

        sqlite3_finalize(stmt);

        return 0;



        

    }

    else{
        sqlite3_finalize(stmt);
        return 1;
    }

    


}