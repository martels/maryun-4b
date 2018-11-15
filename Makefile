main: main.o sudoku.o
	g++ main.o sudoku.o -o main

main.o: main.cpp
	g++ -Wall -Wno-deprecated -c main.cpp

sudoku.o: sudoku.cpp
	g++ -Wall -Wno-deprecated -c sudoku.cpp

clean:
	rm sudoku.o main.o main
