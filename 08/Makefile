CC=g++
CFLAGS=-c -std=c++17 -pthread
LDFLAGS=-std=c++17 -pthread

all: main

main: main_
	./main

test: main_
	./main

main_: main.o test.o thrpool.o
	$(CC) $(LDFLAGS) main.o test.o thrpool.o -o main

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp -o main.o

test.o: test.cpp
	$(CC) $(CFLAGS) test.cpp -o test.o

thrpool.o: thrpool.cpp thrpool.tpp thrpool.hpp
	$(CC) $(CFLAGS) thrpool.cpp -o thrpool.o

clean:
	rm -f main test *.o