#include "sudoku.h"
#include <iostream>

using namespace std;

int main()
{
  ifstream fin;

  // Read the sample grid from the file.
  string fileName = "sudoku5.txt";

  fin.open(fileName.c_str());
  if (!fin)
  {
    cerr << "Cannot open " << fileName << endl;
    exit(1);
  }

  try
  {
    board b1(SquareSize);

    while (fin && fin.peek() != 'Z')
    {
      b1.initialize(fin);
      b1.printOriginal();
      b1.updatePossible();
      b1.solve();
    }
    exit(1);
  }
  catch (indexRangeError &ex)
  {
    cout << ex.what() << endl;
    exit(1);
  }
}
