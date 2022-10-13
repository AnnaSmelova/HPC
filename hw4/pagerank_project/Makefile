CC=/usr/local/opt/llvm/bin/clang

CFLAGS=-Xpreprocessor -fopenmp -c -Wall -g -O3

all: pagerank

pagerank: pagerank_main.o pagerank_lib.a
	$(CC) -fopenmp pagerank_main.o pagerank_lib.a -o pagerank.exe

pagerank_main.o: pagerank_main.c
	$(CC) $(CFLAGS) pagerank_main.c

pagerank_lib.o: pagerank_lib.c
	$(CC) $(CFLAGS) pagerank_lib.c

pagerank_lib.a: pagerank_lib.o
	ar rcs pagerank_lib.a pagerank_lib.o

clean:
	rm -rf *.o *.a pagerank.exe