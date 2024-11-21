#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include<cassert>
#include "simulation.h"
using namespace std;

int main( int argc, char* argv[]) {
    if (argc < 4) {
        cout << "Error: Missing arguments!" <<endl;
        cout << "Usage: ./p3 <species-summary> <world-file> <rounds> [v|verbose]" <<endl;
        return 0;
    }
    
    string SpeciesFile = argv[1];
    string WorldFile = argv[2];
    int turns = atoi(argv[3]);
    if (turns < 0 ) {
        cout << "Error: Number of simulation rounds is negative!" <<endl;
        return 0;
    }
    bool verbose=false;
    if (argc == 5 ) {
        if (string(argv[4])=="v" || string(argv[4])=="verbose") 
            verbose = true;
    }
    
    world_t world;
    if (!initWorld(world, SpeciesFile, WorldFile)) {
        return 0;
    }
    cout << "Initial state" <<endl;
    printGrid(world.grid);
    for (int turn = 1 ; turn <= turns ; turn ++) {
        cout << "Round " << turn << endl;
        for (unsigned int i=0;i < world.numCreatures;i++) {
            simulateCreature (world.creatures[i],world.grid,verbose);
        }
        if (verbose == false) printGrid(world.grid);
        
    }

    return 0;
}