CC = g++
CFLAGS = -g -Wall
target = main

all: main

main: main.cpp
	g++ -g -Wall main.cpp -Isrc/include -Lsrc/lib -lSDL2 -lSDL2main -lmingw32 -o main 

clean: 
	del main.exe