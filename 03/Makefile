CC=g++
CFLAGS=-c -std=c++17
LDFLAGS=-std=c++17

all: main

main: main_
	./main

test: main_
	./main

main_: main.o test.o matrix.o row.o
	$(CC) $(LDFLAGS) main.o test.o matrix.o row.o -o main

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp -o main.o

test.o: test.cpp
	$(CC) $(CFLAGS) test.cpp -o test.o

matrix.o: matrix.cpp
	$(CC) $(CFLAGS) matrix.cpp -o matrix.o

row.o: row.cpp
	$(CC) $(CFLAGS) row.cpp -o row.o

clean:
	rm -f main test *.o
