#include <iostream>
#include <cstdlib>
#include "sea.h"
#include "ocean.h"
#include <thread>
#include <algorithm>

using namespace std;

Ocean::Ocean(){ // a
   Sea* S = new Sea(0, 0, true);
   seas.push_back(S);
}

void Ocean::SimulateOneStep(){
    vector<thread> threads;
    for(auto& sea : seas){
       threads.push_back(thread([&sea]()
        {
            sea->SimulateOneStep();    // run threads in parallel for sea.SimulateOneStep
        }));
       }
       for_each(threads.begin(), threads.end(), [](thread &t){
             t.join();    // join them once they're finished
        });
    for(auto& sea : seas){
        for(int i = 0; i<SIZE; i++){ // iterate through buffers
        if(!sea->left_buffer[i].empty()){ // check if the vector in left buffer is empty
            if(sea->left == nullptr){ // if left doesn't exist then create a new Sea
               MakeAndConnectSea(sea->startx - SIZE, sea->starty);
            }
            for(auto& fptr: sea->left_buffer[i]){
            sea->left->cells[SIZE-1][i].push_back(fptr); // push back to right edge of the adjacent sea
            }
        }
         else if(!sea->right_buffer[i].empty()){ // check if the vector in right buffer is empty
            if(sea->right == nullptr){ // if right doesn't exist then create a new Sea
                 MakeAndConnectSea(sea->startx + SIZE, sea->starty);
            }
            for(auto& fptr: sea->right_buffer[i]){
            sea->right->cells[0][i].push_back(fptr); // push back to left edge of the adjacent sea
            }
        }
         else if(!sea->up_buffer[i].empty()){ // check if the vector in up buffer is empty
            if(sea->above == nullptr){ // if above doesn't exist then create a new Sea
                MakeAndConnectSea(sea->startx, sea->starty-SIZE);
            }
            for(auto& fptr: sea->up_buffer[i]){
            sea->above->cells[i][SIZE-1].push_back(fptr); // push back to bottom edge of the adjacent sea
            }
        }
          else if(!sea->down_buffer[i].empty()){ // check if the vector in down buffer is empty
            if(sea->below == nullptr){ // if below doesn't exist then create a new Sea
                MakeAndConnectSea(sea->startx, sea->starty+SIZE);
            }
            for(auto& fptr: sea->down_buffer[i]){
            sea->below->cells[i][0].push_back(fptr); // push back to top edge of the adjacent sea
            }
        }
        }
    }
    if(seas.size() >= max_seas){ // if number of seas is greater than max_seas throw exception
        throw string("Exception caught: Too many seas exception");
    }
}

void Ocean::MakeAndConnectSea(int sx, int sy){
  Sea* newS = new Sea(sx, sy, false);
   for(auto& sea : seas){
       if(sea->startx == sx + SIZE && sea->starty == sy){ // if new sea is in expected left of a sea, that sea's left is the new sea and new sea's right is that sea
          sea->left = newS;
          newS->right = sea;
       }
       else if(sea->startx== sx - SIZE  && sea->starty == sy){ // if new sea is in expected right of a sea, that sea's right is the new sea and new sea's left is that sea
          sea->right = newS;
          newS->left = sea;
       }
        else if(sea->startx == sx && sea->starty == sy+SIZE){ // if new sea is in expected above of a sea, that sea's above is the new sea and new sea's below is that sea
          sea->above = newS;
          newS->below = sea;
       }
        else if(sea->startx == sx && sea->starty == sy-SIZE){ // if new sea is in expected below of a sea, that sea's below is the new sea and new sea's above is that sea
          sea->below = newS;
          newS->above = sea;
       }
   }
   seas.push_back(newS); // now push new sea back

 if(min_x > sx){  // update these static variables if necessary
    min_x = sx;
 }
 else if (max_x < sx){
    max_x = sx;
 }
 if(min_y > sy){
    min_y = sy;
 }
  else if (max_y < sy){
    max_y = sy;
 }
}

void Ocean::Print(){
    cout << "min_x: "<<min_x<<endl;
    cout << "min_y: "<<min_y<<endl;
    cout << "max_x: "<<max_x<<endl;
    cout << "max_y: "<<max_y<<endl;
    cout << "num_seas: "<< seas.size()<<endl;

    int i = min_x; // i/j keep track of sea block, starting from the beginning
    int j = min_y;
    int jCount = 0; // used to update next sea block once current block is finished iterating
    int iCount = 0;
            for(int j1 = min_y; j1 < max_y + SIZE; j1++ ){   // i1/j1 keep track of cell blocks
            for(int i1 = min_x; i1 < max_x + SIZE; i1++){
            Sea* s = nullptr; // initialize as nullptr

             for(auto& sea : seas){ // find a sea that matches the startx and starty
                 if(sea->startx == i && sea->starty == j){
                    s = sea;
                 }
             }
             if(s == nullptr){
                cout << "x"; // if sea doesnt exist then print x
             }
             else{ // sea does exist
                 if(s->cells [i1-i][j1-j].size() > 9 ){ // check if vector at that cell is greater than 9
                    cout << "M";
                 }
                 else{
                    cout << to_string(s -> cells [i1-i][j1-j].size());
                 }
             }
               iCount++;
               if(iCount == SIZE){ // when iCount reaches 8, we reached the end of sea and update i to next sea
                i += SIZE;
                iCount = 0;
            }

           }
            i = min_x; // reset i
            cout << endl; // make new line at the end of the cell row
            jCount++;
            if(jCount == SIZE){ // when jCount reaches 8, we reached the end of sea and update j to next sea
                j += SIZE;
                jCount = 0;
            }
          }


}

void Ocean:: PopulationCensus(int& nshark, int& nfish){
  nshark = 0;
  nfish = 0;
  int sharkCount = 0;
  int fishCount = 0;
   vector<thread> threads;
    for(auto& sea : seas){
       threads.push_back(thread([&sea, &nshark, &nfish, &sharkCount, &fishCount]()
        {
            sea->Sea::PopulationCensus(sharkCount, fishCount);    // run threads in parallel for sea.PopulationCensus
            nshark+=sharkCount;
            nfish+=fishCount;
        }));
       }

       for_each(threads.begin(), threads.end(), [](thread &t){
             t.join();    // join them once they're finished
        });
}

