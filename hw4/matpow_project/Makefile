CC=/usr/local/opt/llvm/bin/clang

CFLAGS=-Xpreprocessor -fopenmp -c -Wall -g -O3

all: matpow

matpow: matpow_main.o matpow_lib.a
	$(CC) -fopenmp matpow_main.o matpow_lib.a -o matpow.exe

matpow_main.o: matpow_main.c
	$(CC) $(CFLAGS) matpow_main.c

matpow_lib.o: matpow_lib.c
	$(CC) $(CFLAGS) matpow_lib.c

matpow_lib.a: matpow_lib.o
	ar rcs matpow_lib.a matpow_lib.o

clean:
	rm -rf *.o *.a matpow.exe