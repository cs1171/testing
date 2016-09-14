INSTPATH = ./

all: test

test: test.o
	cc -o test test.o

test.o: test.s
	cc -c test.s

test.s:	test.c
	cc -S test.c

clean:
	rm -rf *~ *.*~ *.o *.s test
