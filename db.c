//Use Sqlite to Add to the DB.
//You have to add function to: Store Master Password Hash
//                             Store Encrypted password and IV (DONE)
//                             Retrieve the encoded hash of the mater password [This is for validateHash]

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



int store_password(char *tag,unsigned char *cipher, unsigned char *iv, int cipher_len, int iv_len){
    sql= "CREATE TABLE IF NOT EXISTS passwords(tag TEXT, cipher BLOB, iv BLOB);";

    sqlite3_stmt *stmt;

    sqlite3_prepare_v2(DB, sql, -1, &stmt, NULL);
    rc= sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    if(rc!= SQLITE_DONE){
        return 1;
    }

    sql= "INSERT OR REPLACE INTO passwords (tag,cipher,iv) VALUES (?,?,?);";
    sqlite3_prepare_v2(DB, sql, -1, &stmt, NULL);

    sqlite3_bind_text(stmt, 1, tag, -1, SQLITE_TRANSIENT);
    sqlite3_bind_blob(stmt, 2, cipher, cipher_len, SQLITE_STATIC);
    sqlite3_bind_blob(stmt, 3, iv, iv_len, SQLITE_STATIC);

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