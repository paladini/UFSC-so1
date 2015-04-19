CC=g++
FLAGS=-std=c++11 -ggdb 

all: compile test

compile: 
	$(CC) -o main.o Queue_Test.cc Queue.cpp $(FLAGS)

test:
	./main

create_lib:
	$(CC) -c Queue.cpp
	ar rvs Queue.a Queue.o 

test_lib:
	$(CC) Queue_Test.cc Queue.a -o main
	./main

clean:
	rm -f *.o
	clear
	clear