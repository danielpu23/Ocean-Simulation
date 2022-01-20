#ifndef SEA_H_INCLUDED
#define SEA_H_INCLUDED

#include <vector>
#include "shark.h"

#define SIZE 8
#define INIT_NUM_FISH 50
#define INIT_NUM_SHARK 0

class Sea {
public:
  // sx and sy are the coordinates of the top left cell of this sea.
  // populate to add fish to sea, empty means initialize empty sea
  Sea(int sx, int sy, bool populate);

  void SimulateOneStep();
  void Print();
  void PopulationCensus(int& nshark, int& nfish);
private:
  std::vector<Fish*> cells[SIZE][SIZE];
  std::vector<Fish*> temp_cells[SIZE][SIZE];

  // Buffers to store fish that move out of the sea for each iteration.
  std::vector<Fish*> up_buffer[SIZE];
  std::vector<Fish*> down_buffer[SIZE];
  std::vector<Fish*> left_buffer[SIZE];
  std::vector<Fish*> right_buffer[SIZE];

  // Top left corner
  int startx;
  int starty;

  // Pointers to adjacent seas
  Sea* above;
  Sea* below;
  Sea* left;
  Sea* right;

  friend class Ocean;
};

#endif // SEA_H_INCLUDED
