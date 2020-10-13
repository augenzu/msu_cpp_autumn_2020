CC=g++
CFLAGS=-c -std=c++17 # -Wall
LDFLAGS=-std=c++17 # -Wall

all: main

main: main_
	./main

main_: main.o allocator.o
	$(CC) $(LDFLAGS) main.o allocator.o -o main

test: test_
	./test

test_: test.o allocator.o
	$(CC) $(LDFLAGS) test.o allocator.o -o test

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp -o main.o

test.o: test.cpp
	$(CC) $(CFLAGS) test.cpp -o test.o

allocator.o: allocator.cpp
	$(CC) $(CFLAGS) allocator.cpp -o allocator.o

clean:
	rm -f main test *.o
