CC=g++
CFLAGS=-c -std=c++17
LDFLAGS=-std=c++17

all: main

main: main_
	./main

test: main_
	./main

main_: main.o test.o serializer.o deserializer.o
	$(CC) $(LDFLAGS) main.o test.o serializer.o deserializer.o -o main

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp -o main.o

test.o: test.cpp
	$(CC) $(CFLAGS) test.cpp -o test.o

serializer.o: serializer.cpp
	$(CC) $(CFLAGS) serializer.cpp -o serializer.o

deserializer.o: deserializer.cpp
	$(CC) $(CFLAGS) deserializer.cpp -o deserializer.o

clean:
	rm -f main test *.o