CC = gcc
CFLAGS = -Wall -Wextra -I. \
         -I/opt/homebrew/opt/openssl@3/include \
         -I/opt/homebrew/opt/argon2/include

LDFLAGS = -L/opt/homebrew/opt/openssl@3/lib \
          -L/opt/homebrew/opt/argon2/lib

LIBS = -lssl -lcrypto -lsqlite3 -largon2

OBJS = Encrypt/main.o Encrypt/encrypt.o db.o
TARGET = check_exe

OBJS2 = CreateHash/main.o CreateHash/createHash.o db.o
TARGET2= create_exe

all: $(TARGET) $(TARGET2)
$(TARGET): $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) $(LIBS) -o $(TARGET)

$(TARGET2): $(OBJS2)
	$(CC) $(OBJS2) $(LDFLAGS) $(LIBS) -o $(TARGET2)



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

