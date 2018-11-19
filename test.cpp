#include <cmath>
#include <iostream>

using namespace std;

int main()
{
  for (double i = 10; i < 11; i++)
  {
    cout << ceil(i / 9) << endl;
  }
}









recurseCount++;
  if(recurseCount%1000 == 0)
  {
    print();
    cout << endl << recurseCount << endl;
  }

  double ind = (double) index;
  int i = ceil(ind/9);
  int j = index%9;
  int picker = 1;
  if(j == 0)
    j = 9;

  if(conflicts() == false)
  {
    return false;
  }
  if(isSolved() == true)
  {
    return true;
  }  
  


  if(original[i][j] != Blank) //possible[i][j].at(0) == 0)
  {
    if(solve(index++) == false)
      return false;
    else
      return true;
  }

if(original[i][j] == Blank)
  {
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