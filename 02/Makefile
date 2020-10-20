CC=g++
CFLAGS=-c -std=c++17
LDFLAGS=-std=c++17

all: test

test: test_
	./test

test_: test.o parser.o
	$(CC) $(LDFLAGS) test.o parser.o -o test

test.o: test.cpp
	$(CC) $(CFLAGS) test.cpp -o test.o

parser.o: parser.cpp
	$(CC) $(CFLAGS) parser.cpp -o parser.o

clean:
	rm -f main test *.o
