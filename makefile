#Makefile

all:	folders
	g++ -o obj/problem.o -c -Werror -std=c++0x -O2 -Iinclude src/problem.cpp
	g++ -o obj/localsearch.o -c -Werror -std=c++0x -O2 -Iinclude src/localsearch.cpp
	g++ -o obj/input.o -c -Werror -std=c++0x -O2 -Iinclude src/input.cpp
	g++ -o obj/greedy.o -c -Werror -std=c++0x -O2 -Iinclude src/greedy.cpp
	g++ -o obj/main.o -c -Werror -std=c++0x -O2 -Iinclude src/main.cpp
	g++ -o bin/qap obj/problem.o obj/input.o obj/localsearch.o obj/greedy.o obj/main.o
folders:
	mkdir -p bin obj

clear:
	rm bin/* obj/*
