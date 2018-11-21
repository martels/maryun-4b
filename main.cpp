#include "sudoku.h"
#include <iostream>
#include <numeric>

using namespace std;


int main()
{
  ifstream fin;

  // Read the sample grid from the file.
  string fileName = "sudoku4-6.txt";

  fin.open(fileName.c_str());
  if (!fin)
  {
    cerr << "Cannot open " << fileName << endl;
    exit(1);
  }

  try
  {
    vector<board*> boards;
    vector<int> counts;
    int index = 0;
    double avg = 0;
    int size = 1;
    boards.resize(size);
    counts.resize(size);

    while (fin && fin.peek() != 'Z')
    {
      while (fin && fin.peek() != 'Z')
      {
        boards.at(index) = new board(SquareSize);
        counts.at(index) = 0;

        boards.at(index)->initialize(fin);
        boards.at(index)->printOriginal();
        boards.at(index)->updatePossible();
        boards.at(index)->solve();
        counts.at(index) = boards.at(index)->RCount();
        counts.at(index) = boards.at(index)->RCount();

        size++;
        index++;

        boards.resize(size);
        counts.resize(size);
      }
    }

    float c_average = accumulate( counts.begin(), counts.end(), 0.0/ counts.size())/counts.size();
    cout << "The average recursive calls of all " << index << " was " << c_average << endl;
    exit(1);
  }
  catch (indexRangeError &ex)
  {
    cout << ex.what() << endl;
    exit(1);
  }
}
