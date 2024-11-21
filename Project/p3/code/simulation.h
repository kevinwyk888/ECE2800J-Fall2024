
#ifndef SIMULATION_H
#define SIMULATION_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include<cassert>
#include "world_type.h"
using namespace std;

bool judgevaild(const point_t &new_point, const grid_t & grid);

bool ifocuppy(const point_t &adjp,const grid_t & grid);

bool initWorld(world_t &world, const string &speciesFile, const string &creaturesFile); 

direction_t encode_instruction(const string &instruction_s);

direction_t encode_direction(const string &direction);

void simulateCreature(creature_t &creature, grid_t &grid, bool verbose); 

void printGrid(const grid_t &grid); 

point_t adjacentPoint(point_t pt, direction_t dir); 

direction_t leftFrom(direction_t dir); 

direction_t rightFrom(direction_t dir); 

instruction_t getInstruction(const creature_t &creature); 

creature_t *getCreature(const grid_t &grid, point_t location);

#endif