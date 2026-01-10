CC = gcc
CFLAGS = -Wall -Wextra
LIBS = -lssl -lcrypto -lsqlite3

OBJS = Encrypt/main.o Encrypt/encrypt.o db.o
TARGET = check_exe

all: $(TARGET)
$(TARGET): $(OBJS)
	$(CC) $(OBJS) $(LIBS) -o $(TARGET)

Encrypt/main.o: Encrypt/main.c Encrypt/encrypt.h db.h
	$(CC) $(CFLAGS) -c Encrypt/main.c -o Encrypt/main.o

Encrypt/encrypt.o: Encrypt/encrypt.c Encrypt/encrypt.h 
	$(CC) $(CFLAGS) -c Encrypt/encrypt.c -o Encrypt/encrypt.o

db.o: db.c db.h
	$(CC) $(CFLAGS) -c db.c -o db.o

