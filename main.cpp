#include <iostream>
#include "hw9.ocean.h"

using namespace std;

const float Shark::max_hunger = 20.0;
float Shark::hunger_increment = 5.0;
int Ocean::min_x = 0;
int Ocean::max_x = 0;
int Ocean::min_y = 0;
int Ocean::max_y = 0;
const int Ocean::max_seas = 12;


int main() {
  int nsharks, nfish;
  Ocean ocean;
  ocean.PopulationCensus(nsharks, nfish);
  cout << "Init num sharks: " << nsharks << " nfish: " << nfish << endl;
  ocean.Print();

  for (int i = 0; i < 25; i++) { // simulate ocean growing 25 times
    try{
    ocean.SimulateOneStep();
    }
    catch(string n){     // catch exception
      cout << n << endl;
      break; // break out
    }
     ocean.PopulationCensus(nsharks, nfish);
    cout << "Step " << i << " num sharks: " << nsharks << " nfish: "
	 << nfish << endl;
    ocean.Print();
  }
  cout << "done" << endl;

  return 0;
}
