#ifndef DB_H
#define DB_H

#include<sqlite3.h>
extern sqlite3 *DB;

int db_init(void);
int store_password(char *tag, unsigned char *cipher, unsigned char *iv, int cipher_len, int iv_len);
int storeHash(char *encoded_hash);

#endif