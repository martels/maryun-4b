#include "d_except.h"
#include "d_matrix.h"
#include <fstream>
#include <iostream>
#include <limits>
#include <list>

using namespace std;

typedef int ValueType; // The type of the value in a cell
const int Blank = -1;  // Indicates that a cell is blank

const int SquareSize = 3; //  The number of cells in a small square
                          //  (usually 3).  The board has
                          //  SquareSize^2 rows and SquareSize^2
                          //  columns.

const int BoardSize = SquareSize * SquareSize;

const int MinValue = 1;
const int MaxValue = 9;

//int numSolutions = 0;

class board
// Stores the entire Sudoku board
{
public:
  // provided member functions
  board(int);
  void clear();
  void initialize(ifstream &fin);
  void print();
  bool isBlank(int, int);
  ValueType getCell(int, int);

  // new member functions Part a
  bool conflicts();
  void setCell(int, int, int);
  void printOriginal();
  void printConflicts();
  bool isSolved();
  void clearUpdate(int, int);
  void addUpdate(int, int, int);

  // Part b member functions
  void updatePossible();
  bool isFull();
  void solve();
  int printCount();

private:
  // The following matrices go from 1 to BoardSize in each
  // dimension, i.e., they are each (BoardSize+1) * (BoardSize+1)
  int recurseCount;
  bool conflictflag; //false for conflicts
  matrix<ValueType> value, original, rows, columns, squares;
  matrix<vector<int>> possible;
};
