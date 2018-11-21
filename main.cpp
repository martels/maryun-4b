#include "sudoku.h"
#include <iostream>

using namespace std;


int main()
{
  ifstream fin;

  // Read the sample grid from the file.
  string fileName = "sudoku1-3.txt";

  fin.open(fileName.c_str());
  if (!fin)
  {
    cerr << "Cannot open " << fileName << endl;
    exit(1);
  }

  try
  {
    board b1(SquareSize);
    board b2(SquareSize);
    board b3(SquareSize);

    int b1count = 0;
    int b2count = 0;
    int b3count = 0;
    double avg = 0;

    while (fin && fin.peek() != 'Z')
    {
      b1.initialize(fin);
      b1.printOriginal();

      b2.initialize(fin);
      b2.printOriginal();

      b3.initialize(fin);
      b3.printOriginal();

      b1.updatePossible();
      b1.solve();
      b1count = b1.printCount();

      b2.updatePossible();
      b2.solve();
      b2count = b1.printCount();

      b3.updatePossible();
      b3.solve();
      b3count = b3.printCount();

      avg = (b3count + b2count + b1count) / 2;
    }
    exit(1);
  }
  catch (indexRangeError &ex)
  {
    cout << ex.what() << endl;
    exit(1);
  }
}
