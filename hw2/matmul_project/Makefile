CC=gcc

CFLAGS=-c -Wall -g -O3

all: matmul

matmul: matmul_main.o matmul_lib.a
	$(CC) matmul_main.o matmul_lib.a -o matmul.exe

matmul_main.o: matmul_main.c
	$(CC) $(CFLAGS) matmul_main.c

matmul_lib.o: matmul_lib.c
	$(CC) $(CFLAGS) matmul_lib.c

matmul_lib.a: matmul_lib.o
	ar rcs matmul_lib.a matmul_lib.o

clean:
	rm -rf *.o *.a matmul.exe