CC=g++
CFLAGS=-c -std=c++17
LDFLAGS=-std=c++17

all: main

main: main_
	./main

test: main
	./main

main_: main.o test.o parser.o
	$(CC) $(LDFLAGS) main.o test.o parser.o -o main

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp -o main.o

test.o: test.cpp
	$(CC) $(CFLAGS) test.cpp -o test.o

parser.o: parser.cpp
	$(CC) $(CFLAGS) parser.cpp -o parser.o

clean:
	rm -f main test *.o
