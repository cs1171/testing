INSTPATH = ./

all: btree

test: btree.o
	cc -o btree btree.o

btree.o: btree.s
	cc -c btree.s

btree.s: btree.c
	cc -S btree.c

clean:
	rm -rf *~ *.*~ *.o *.s btree
