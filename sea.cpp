#include <iostream>
#include <cstdlib>
#include "hw9.sea.h"
#include <mutex>
using namespace std;


mutex m1;

Sea::Sea(int sx, int sy, bool populate) : startx(sx), starty(sy) {
  above = below = left = right = nullptr;
  if (populate) {
    for (int i = 0; i < INIT_NUM_FISH; i++) {
      Fish* fptr = new Fish;
      int x = rand() % SIZE;
      int y = rand() % SIZE;
      cells[x][y].push_back(fptr);
    }
    for (int i = 0; i < INIT_NUM_SHARK; i++) {
      Fish* fptr = new Shark;
      int x = rand() % SIZE;
      int y = rand() % SIZE;
      cells[x][y].push_back(fptr);
    }
  }
}

void Sea::SimulateOneStep() {
  unique_lock<mutex> L1 (m1); // put a lock here to make sure no other thread can access
  for(auto & buffer : left_buffer){ // clear buffers at start
      buffer.clear();
  }
  for(auto & buffer : right_buffer){
     buffer.clear();
  }
  for(auto & buffer : up_buffer){
      buffer.clear();
  }
   for(auto & buffer : down_buffer){
      buffer.clear();
  }
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      temp_cells[i][j].clear();
    }
  }
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      vector<Fish*> to_delete;
      for (Fish* fptr : cells[i][j]) {
	fptr->Grow();
	if (!fptr->IsAlive()) {
	  to_delete.push_back(fptr);
	  continue;
	}
	fptr->Eat(cells[i][j]);
	Fish* baby_fish = fptr->Reproduce();
	if (baby_fish != nullptr) {
	  temp_cells[i][j].push_back(baby_fish);
	}
	int ni = i;
	int nj = j;
	int move_dir = rand() % 4;
	switch(move_dir) {
	case 0:
	  ni++;
	  break;
	case 1:
	  ni--;
	  break;
	case 2:
	  nj++;
	  break;
	case 3:
	  nj--;
	  break;
	}

	if ((ni < 0) || (ni >= SIZE) ||
	    (nj < 0) || (nj >= SIZE)) {
        to_delete.push_back(fptr);
        if(ni < 0) { // move left
            Fish* fishptr = new Fish(*fptr); // copy the fish from fptr so when it's deleted from the original sea, it's not deleted in new sea
            left_buffer[nj].push_back(fishptr);
	  }
	  else if (ni >= SIZE){ // move right
            Fish* fishptr = new Fish(*fptr); // copy the fish from fptr so when it's deleted from the original sea, it's not deleted in new sea
            right_buffer[nj].push_back(fishptr);
	  }
	  else if (nj < 0) { // move up
            Fish* fishptr = new Fish(*fptr); // copy the fish from fptr so when it's deleted from the original sea, it's not deleted in new sea
            up_buffer[ni].push_back(fishptr);
	  }
	   else if (nj >= SIZE) { // move down
            Fish* fishptr = new Fish(*fptr); // copy the fish from fptr so when it's deleted from the original sea, it's not deleted in new sea
            down_buffer[ni].push_back(fishptr);
	  }
	} else {
	  temp_cells[ni][nj].push_back(fptr);
	}

      }

      for (Fish* fptr : to_delete) {
	delete fptr;
      }
    }
  }

  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      cells[i][j].clear();
      cells[i][j] = temp_cells[i][j];
    }
  }
}

// Note: This function has been changed from HW 8.
// For each cell print the number of fish in the cell.
void Sea::Print() {
  cout << "startx: " << startx << endl;
  cout << "starty: " << starty << endl;

  for (int j = 0; j < SIZE; j++) {
    for (int i = 0; i < SIZE; i++) {
      cout << cells[i][j].size();
    }
    cout << endl;
  }
  cout << endl;
}

void Sea::PopulationCensus(int& nshark, int& nfish) {
  unique_lock<mutex> L1 (m1); // put a lock here to make sure no other thread can access
  nshark = 0;
  nfish = 0;
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      for (Fish* fptr : cells[i][j]) {
	if (fptr->IsEdible() && fptr->IsAlive()) {
	  nfish++;
	} else if (!fptr->IsEdible()) {
	  nshark++;
	}
      }
    }
  }

}


