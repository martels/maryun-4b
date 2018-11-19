#include "sudoku.h"
#include <cmath>

using namespace std;

board::board(int sqSize)
    : value(BoardSize + 1, BoardSize + 1),
      original(BoardSize + 1, BoardSize + 1),
      rows(BoardSize + 1, BoardSize + 1), columns(BoardSize + 1, BoardSize + 1),
      squares(BoardSize + 1, BoardSize + 1), possible(BoardSize + 1, BoardSize + 1), recurseCount(0)
// Board constructor
{
  clear();
    conflictflag = true;
    for(int i = 1; i <= BoardSize; i++)
      for(int j = 1; j <= BoardSize; j++)
      {
        possible[i][j].resize(BoardSize + 1);
      }
}

void board::clear()
// Mark all possible values as legal for each board entry
{
  for (int i = 1; i <= BoardSize; i++)
    for (int j = 1; j <= BoardSize; j++)
    {
      value[i][j] = Blank;
      original[i][j] = Blank;
    }
}

void board::initialize(ifstream &fin)
// Read a Sudoku board from the input file.
{
  char ch;

  clear();

  for (int i = 1; i <= BoardSize; i++)
    for (int j = 1; j <= BoardSize; j++)
    {
      fin >> ch;

      // If the read char is not Blank
      if (ch != '.')
        setCell(i, j, ch - '0'); // Convert char to int
    }

  original = value;
}

int squareNumber(int i, int j)
// Return the square number of cell i,j (counting from left to right,
// top to bottom.  Note that i and j each go from 1 to BoardSize
{
  // Note that (int) i/SquareSize and (int) j/SquareSize are the x-y
  // coordinates of the square that i,j is in.

  return SquareSize * ((i - 1) / SquareSize) + (j - 1) / SquareSize + 1;
}

ostream &operator<<(ostream &ostr, vector<int> &v)
// Overloaded output operator for vector class.
{
  for (int i = 0; i < v.size(); i++)
    ostr << v[i] << " ";
  cout << endl;
    return ostr;
}

ValueType board::getCell(int i, int j)
// Returns the value stored in a cell.  Throws an exception
// if bad values are passed.
{
  if (i >= 1 && i <= BoardSize && j >= 1 && j <= BoardSize)
    return value[i][j];
  else
    throw rangeError("bad value in getCell");
}

bool board::isBlank(int i, int j)
// Returns true if cell i,j is blank, and false otherwise.
{
  if (i < 1 || i > BoardSize || j < 1 || j > BoardSize)
    throw rangeError("bad value in setCell");

  return (getCell(i, j) == Blank);
}

void board::print()
// Prints the current board.
{
  for (int i = 1; i <= BoardSize; i++)
  {
    if ((i - 1) % SquareSize == 0)
    {
      cout << " -";
      for (int j = 1; j <= BoardSize; j++)
        cout << "---";
      cout << "-";
      cout << endl;
    }
    for (int j = 1; j <= BoardSize; j++)
    {
      if ((j - 1) % SquareSize == 0)
        cout << "|";
      if (!isBlank(i, j))
        cout << " " << getCell(i, j) << " ";
      else
        cout << "   ";
    }
    cout << "|";
    cout << endl;
  }

  cout << " -";
  for (int j = 1; j <= BoardSize; j++)
    cout << "---";
  cout << "-";
  cout << endl;
}

//-------------------------Part a-------------------------------//


void board::printOriginal()
// Prints the original board.
{
  for (int i = 1; i <= BoardSize; i++)
  {
    if ((i - 1) % SquareSize == 0)
    {
      cout << " -";
      for (int j = 1; j <= BoardSize; j++)
        cout << "---";
      cout << "-";
      cout << endl;
    }
    for (int j = 1; j <= BoardSize; j++)
    {
      if ((j - 1) % SquareSize == 0)
        cout << "|";
      if (!isBlank(i, j))
        cout << " " << getCell(i, j) << " ";
      else
        cout << "   ";
    }
    cout << "|";
    cout << endl;
  }

  cout << " -";
  for (int j = 1; j <= BoardSize; j++)
    cout << "---";
  cout << "-";
  cout << endl;
}

void board::setCell(int i, int j, int num)
// sets the cell at i and j
{
  if (num <= BoardSize && num > 0 && original[i][j] == Blank)
  {
    value[i][j] = num;
  }
  return;
}

bool board::conflicts()
{
  int temp = 0;
  this->conflictflag = true;

  // set matrices to 0
  for (int i = 1; i <= BoardSize; i++)
    for (int j = 1; j <= BoardSize; j++)
    {
      rows[i][j] = 0;
      squares[i][j] = 0;
      columns[i][j] = 0;
    }

  // count the number of times a number apears in a row
  for (int i = 1; i <= BoardSize; i++)
    for (int j = 1; j <= BoardSize; j++)
    {

        temp = value[i][j];
        rows[i][temp] = rows[i][temp] + 1;
        
        int sqNum = squareNumber(i,j);
        squares[sqNum][temp] = squares[sqNum][temp] +1;
        

        temp = value[j][i];
        columns[i][temp] = columns[i][temp] + 1;
    }


    for (int i = 1; i <= BoardSize; i++)
    for (int j = 1; j <= BoardSize; j++)
    {
      if (rows[i][j] > 1 || squares[i][j] > 1 || columns[i][j] > 1)
      {
          
          this->conflictflag = false;
      }
    }
    return conflictflag;
}

void board::printConflicts()
// updates conflict matrices, prints the board as it stands and prints the
// conflicts found
{
    conflicts();
    print();
    if (!conflictflag)
  {
  for (int i = 1; i <= BoardSize; i++)
    for (int j = 1; j <= BoardSize; j++)
      {
        if (rows[i][j] >= 2)
        {
          cout << "Conflict! More than one '" << j << "' in row "
            << i << endl;
        }

        if (squares[i][j] >= 2)
        {
          cout << "Conflict! More than one '" << j << "' in square "
               << i << endl;
        }

        if (columns[i][j] >= 2)
        {
          cout << "Conflict! More than one '" << j << "' in column "
               << i << endl;
        }
      }
  }
    else
        cout << "No conflicts\n";
}

bool board::isFull()
{
  bool full = true;

  for(int i = 1; i <= BoardSize; i++)
    for(int j = 1; j <= BoardSize; j++)
    {
      if(value[i][j] == -1)
        full = false;
    }
    return full;
}

bool board::isSolved()
{
  conflicts();

  if(conflictflag == true && isFull() == true)
    return true;
  else
    return false;
}

void board::clearUpdate(int i, int j)
{
  if (original[i][j] == Blank)
  {
    value[i][j] = Blank;
  }

  conflicts();
}

void board::addUpdate(int i, int j, int val)
{
  setCell(i, j, val);
  conflicts();
}

//------------------------------------Part b----------------------------------------------//

void board::updatePossible()
{
  conflicts();
  int temp = 0;
  for(int i = 1; i <= BoardSize; i++)
    for(int j = 1; j <= BoardSize; j++)
      for(int k =  0; k <= BoardSize; k++)
      {
        possible[i][j].at(k) = 1;
      }
    


  for(int i = 1; i <= BoardSize; i++)
    for(int j = 1; j <= BoardSize; j++)
      for(int k = 1; k <= BoardSize; k++)
      {
        if(rows[i][k] > 0 || columns[j][k] > 0 || squares[squareNumber(i, j)][k] > 0 || original[i][j] != Blank)
        {
            possible[i][j].at(k) = 0;
        }

        if(original[i][j] != Blank)
        {
          possible[i][j].at(0) = 0; 
        }
      }

// cout << "possible" << endl;

//   for(int i = 1; i <= BoardSize; i++)
//   { 
//     cout << "Row " << i << endl; 
//     for(int j = 1; j <= BoardSize; j++)
//     {  
//       cout << "| ";
//       for(int k = 0; k <= BoardSize; k++)
//       {
//         cout << possible[i][j].at(k) << " ";
//       }
//       cout << "|" << endl;
//     }
//   }

}

void board::solve(int index)
{
  recurseCount++:

  if(isSolved())
  {
    print();
    return
  }

  int index = 1;
  double ind = (double) index;
  int i = ceil(ind/9);
  int j = index%9;
  if(j == 0)
    j = 9;

  while(value[i][j] != Blank)
  {
    index++;
    ind = (double) index;
    i = ceil(ind/9);
    j = index%9;
    if(j == 0)
      j = 9;
  }

  while(picker < 10)
    {
      while(possible[i][j].at(picker) != 1 && picker < 9)
      {
        picker++;
      }

      setCell(i, j, picker);
      if(solve(index++) == true)
      {
        return true;
      }
      else
      {
        possible[i][j].at(picker) = 0;
      }
    }
    return false;
  

  
}