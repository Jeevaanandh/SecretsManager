#ifndef DB_H
#define DB_H

#include<sqlite3.h>
extern sqlite3 *DB;

int db_init(void);
int store_password(char *tag,unsigned char *cipher, unsigned char *iv, unsigned char *salt, int cipher_len, int iv_len, int salt_len);
int storeHash(char *encoded_hash);
int get_hash_fromDB(char *encoded_hash, size_t hashlen);
int get_cipher_fromDB(char * tag, char *storeTag, unsigned char *cipher, unsigned char *iv, unsigned char *salt, size_t t_len, int *cipher_size, int *iv_size, int *salt_size);

#endif