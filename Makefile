CC = gcc
CFLAGS = -Wall -Wextra -I. \
         -I/opt/homebrew/opt/openssl@3/include \
         -I/opt/homebrew/opt/argon2/include

LDFLAGS = -L/opt/homebrew/opt/openssl@3/lib \
          -L/opt/homebrew/opt/argon2/lib

LIBS = -lssl -lcrypto -lsqlite3 -largon2


OBJS2 = CreateHash/main.o CreateHash/createHash.o db.o
TARGET2= create_exe






OBJS5= CLI.o Encrypt/encrypt_main.o Encrypt/encrypt.o CreateHash/createHash.o ValidateHash/validate_main.o ValidateHash/validateHash.o Decrypt/decrypt_main.o Decrypt/decrypt.o db.o 
TARGET5 = dpa

all: $(TARGET2) $(TARGET3) $(TARGET5)


$(TARGET2): $(OBJS2)
	$(CC) $(OBJS2) $(LDFLAGS) $(LIBS) -o $(TARGET2)








$(TARGET5): $(OBJS5)
	$(CC) $(OBJS5) $(LDFLAGS) $(LIBS) -o $(TARGET5)



CLI.o: CLI.c Encrypt/encrypt_main.h Decrypt/decrypt.h Decrypt/decrypt_main.h db.h
	$(CC) $(CFLAGS) -c CLI.c -o CLI.o


Decrypt/decrypt_main.o: Decrypt/decrypt_main.c Decrypt/decrypt.h Decrypt/decrypt_main.h ValidateHash/validateHash.h CreateHash/createHash.h db.h
	$(CC) $(CFLAGS) -c Decrypt/decrypt_main.c -o Decrypt/decrypt_main.o


Decrypt/decrypt.o: Decrypt/decrypt.c Decrypt/decrypt.h
	$(CC) $(CFLAGS) -c Decrypt/decrypt.c -o Decrypt/decrypt.o


ValidateHash/validate_main.o: ValidateHash/validate_main.c ValidateHash/validate_main.h ValidateHash/validateHash.h db.h
	$(CC) $(CFLAGS) -c ValidateHash/validate_main.c -o ValidateHash/validate_main.o


ValidateHash/validateHash.o: ValidateHash/validateHash.c ValidateHash/validateHash.h 
	$(CC) $(CFLAGS) -c ValidateHash/validateHash.c -o ValidateHash/validateHash.o



CreateHash/main.o: CreateHash/main.c CreateHash/createHash.h db.h
	$(CC) $(CFLAGS) -c CreateHash/main.c -o CreateHash/main.o


CreateHash/createHash.o: CreateHash/createHash.c CreateHash/createHash.h 
	$(CC) $(CFLAGS) -c CreateHash/createHash.c -o CreateHash/createHash.o



Encrypt/encrypt_main.o: Encrypt/encrypt_main.c Encrypt/encrypt.h CreateHash/createHash.h db.h Encrypt/encrypt_main.h
	$(CC) $(CFLAGS) -c Encrypt/encrypt_main.c -o Encrypt/encrypt_main.o

Encrypt/encrypt.o: Encrypt/encrypt.c Encrypt/encrypt.h 
	$(CC) $(CFLAGS) -c Encrypt/encrypt.c -o Encrypt/encrypt.o

db.o: db.c db.h
	$(CC) $(CFLAGS) -c db.c -o db.o

