CC=g++
FLAGS=-c -g
LIB=-lm

all: 
	$(CC) main.cpp -o main.o $(FLAGS)
	$(CC) SimpleApplication.cpp -o SimpleApplication.o $(FLAGS)
	$(CC) -o SimApp main.o SimpleApplication.o $(LIB) -g

exe: main.cpp SimpleApplication.cpp
	$(CC) -o SimApp main.o SimpleApplication.o $(LIB) -g

clean:
	rm -f *.o
	rm -f SimApp


