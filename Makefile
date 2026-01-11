CC = gcc
CFLAGS = -Wall -Wextra -I. \
         -I/opt/homebrew/opt/openssl@3/include \
         -I/opt/homebrew/opt/argon2/include

LDFLAGS = -L/opt/homebrew/opt/openssl@3/lib \
          -L/opt/homebrew/opt/argon2/lib

LIBS = -lssl -lcrypto -lsqlite3 -largon2

OBJS = Encrypt/main.o Encrypt/encrypt.o db.o
TARGET = encrypt_exe

OBJS2 = CreateHash/main.o CreateHash/createHash.o db.o
TARGET2= create_exe


OBJS3 = ValidateHash/main.o ValidateHash/validateHash.o db.o 
TARGET3 = validate_exe

OBJS4= Decrypt/main.o Decrypt/decrypt.o ValidateHash/validateHash.o db.o 
TARGET4 = decrypt_exe

all: $(TARGET) $(TARGET2) $(TARGET3) $(TARGET4)
$(TARGET): $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) $(LIBS) -o $(TARGET)

$(TARGET2): $(OBJS2)
	$(CC) $(OBJS2) $(LDFLAGS) $(LIBS) -o $(TARGET2)


$(TARGET3): $(OBJS3)
	$(CC) $(OBJS3) $(LDFLAGS) $(LIBS) -o $(TARGET3)


$(TARGET4): $(OBJS4)
	$(CC) $(OBJS4) $(LDFLAGS) $(LIBS) -o $(TARGET4)




Decrypt/main.o: Decrypt/main.c Decrypt/decrypt.h ValidateHash/validateHash.h db.h
	$(CC) $(CFLAGS) -c Decrypt/main.c -o Decrypt/main.o


Decrypt/decrypt.o: Decrypt/decrypt.c Decrypt/decrypt.h
	$(CC) $(CFLAGS) -c Decrypt/decrypt.c -o Decrypt/decrypt.o


ValidateHash/main.o: ValidateHash/main.c ValidateHash/validateHash.h db.h
	$(CC) $(CFLAGS) -c ValidateHash/main.c -o ValidateHash/main.o


ValidateHash/validateHash.o: ValidateHash/validateHash.c ValidateHash/validateHash.h 
	$(CC) $(CFLAGS) -c ValidateHash/validateHash.c -o ValidateHash/validateHash.o



CreateHash/main.o: CreateHash/main.c CreateHash/createHash.h db.h
	$(CC) $(CFLAGS) -c CreateHash/main.c -o CreateHash/main.o


CreateHash/createHash.o: CreateHash/createHash.c CreateHash/createHash.h 
	$(CC) $(CFLAGS) -c CreateHash/createHash.c -o CreateHash/createHash.o



Encrypt/main.o: Encrypt/main.c Encrypt/encrypt.h db.h
	$(CC) $(CFLAGS) -c Encrypt/main.c -o Encrypt/main.o

Encrypt/encrypt.o: Encrypt/encrypt.c Encrypt/encrypt.h 
	$(CC) $(CFLAGS) -c Encrypt/encrypt.c -o Encrypt/encrypt.o

db.o: db.c db.h
	$(CC) $(CFLAGS) -c db.c -o db.o

