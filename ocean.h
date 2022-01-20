#ifndef OCEAN_H
#define OCEAN_H

#include <vector>
#include "sea.h"

using namespace std;

class Ocean {
 public:
  // 2. (1 point)
  // Start with one Sea and populate that Sea with some fish.
  Ocean();
  void SimulateOneStep();
  void MakeAndConnectSea(int sx, int sy);
  void Print();
  void PopulationCensus(int& nshark, int& nfish);
 private:
  vector<Sea*> seas;

  static int min_x;
  static int max_x;
  static int min_y;
  static int max_y;
  static const int max_seas;
};

#endif
