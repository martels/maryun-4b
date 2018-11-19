#include "sudoku.h"
#include <iostream>

using namespace std;

void solve(board &sudoku)
{
  sudoku.recurseCount++;

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
      while(possible[i][j].at(picker) != 1 && picker < 10)
      {
        picker++;
      }

      setCell(i, j, picker);
      solve();

      
    }
    return false;
  
}