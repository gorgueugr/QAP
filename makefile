#Makefile

all:	folders
	g++ -o obj/random.o -c -Werror -std=c++0x -O2 -Iinclude src/random.cpp -fopenmp
	g++ -o obj/problem.o -c -Werror -std=c++0x -O2 -Iinclude src/problem.cpp -fopenmp
	g++ -o obj/localsearch.o -c -Werror -std=c++0x -O2 -Iinclude src/localsearch.cpp -fopenmp
	g++ -o obj/input.o -c -Werror -std=c++0x -O2 -Iinclude src/input.cpp -fopenmp
	g++ -o obj/greedy.o -c -Werror -std=c++0x -O2 -Iinclude src/greedy.cpp -fopenmp
	g++ -o obj/genetic.o -c -Werror -std=c++0x -O2 -Iinclude src/genetic.cpp -fopenmp
	g++ -o obj/memetic.o  -c -Werror -std=c++0x -O2 -Iinclude src/memetic.cpp -fopenmp
	g++ -o obj/main.o -c -Werror -std=c++0x -O2 -Iinclude src/main.cpp -fopenmp
	g++ -o bin/qap  obj/memetic.o obj/genetic.o obj/problem.o  obj/input.o obj/localsearch.o obj/greedy.o  obj/random.o obj/main.o -fopenmp
folders:
	mkdir -p bin obj

clear:
	rm bin/* obj/*
