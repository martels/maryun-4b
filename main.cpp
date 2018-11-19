#include "sudoku.h"
#include <iostream>

using namespace std;

int main()
{
  ifstream fin;

  // Read the sample grid from the file.
  string fileName = "sudoku2.txt";

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
      b1.print();

      // b1.addUpdate(3, 3, 3);
      // b1.addUpdate(4, 4, 2);
      // b1.addUpdate(4, 5, 2);
      // b1.printConflicts();
      // b1.clearUpdate(4, 4);
      // b1.clearUpdate(4, 5);
      // b1.clearUpdate(3, 1);
      // b1.printConflicts();
    }
    exit(1);
  }
  catch (indexRangeError &ex)
  {
    cout << ex.what() << endl;
    exit(1);
  }
}
