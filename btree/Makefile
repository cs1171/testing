INSTPATH = ./

all: btree

btree: btree.o main.o
	cc -o btree btree.o main.o

btree.o: btree.c btree.h
	cc -c btree.c

main.o: main.c btree.h
	cc -c main.c

clean:
	rm -rf *~ *.*~ *.o *.s btree
