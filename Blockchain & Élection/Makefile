CC = gcc
CFLAGS = -g -Wall

all : main

main : main.c generateData.o winner.o maths.o rsa.o key.o signature.o protected.o listKey.o listProtected.o hash.o block.o tree.o
	$(CC) $(CFLAGS) -o main main.c generateData.o maths.o rsa.o key.o signature.o protected.o listKey.o listProtected.o hash.o block.o tree.o -lm -lssl -lcrypto

maths.o : maths.c maths.h 
	$(CC) $(CFLAGS) -c maths.c 

rsa.o : rsa.c rsa.h maths.o maths.h
	$(CC) $(CFLAGS) -c rsa.c

key.o : key.c key.h rsa.o rsa.h
	$(CC) $(CFLAGS) -c key.c

signature.o : signature.c signature.h key.o key.h
	$(CC) $(CFLAGS) -c signature.c 

protected.o : protected.c protected.h signature.o signature.h
	$(CC) $(CFLAGS) -c protected.c 

generateData.o : generateData.c generateData.h key.o key.h signature.o signature.h protected.o protected.h
	$(CC) $(CFLAGS) -c generateData.c 

listKey.o : listKey.c listKey.h key.o key.h
	$(CC) $(CFLAGS) -c listKey.c

listProtected.o : listProtected.c listProtected.h protected.o protected.h
	$(CC) $(CFLAGS) -c listProtected.c 

hash.o : hash.c hash.h listKey.o listKey.h listProtected.o listProtected.h
	$(CC) $(CFLAGS) -c hash.c

winner.o : winner.c hash.o hash.h
	$(CC) $(CFLAGS) -c winner.c 

block.o : block.c block.h hash.o hash.h
	$(CC) $(CFLAGS) -c block.c

tree.o : tree.c tree.h block.o block.h
	$(CC) $(CFLAGS) -c tree.c

blockTree.o : blockTree.c blockTree.h tree.o tree.h
	$(CC) $(CFLAGS) -c blockTree.c

#Effacer les .o et les executables
#Pour executer cette regle il faut taper dans le terminal "make clean"
clean : 
	rm *.o main
