#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include<cassert>
#include "world_type.h"
using namespace std;
    
opcode_t encode_instruction(const string &instruction_s) {
    if (instruction_s == "hop") return HOP;
    if (instruction_s == "left") return LEFT;
    if (instruction_s == "right") return RIGHT;
    if (instruction_s == "infect") return INFECT;
    if (instruction_s == "ifempty") return IFEMPTY;
    if (instruction_s == "ifenemy") return IFENEMY;
    if (instruction_s == "ifsame") return IFSAME;
    if (instruction_s == "ifwall") return IFWALL;
    return GO;   
}
direction_t encode_direction(const string &direction) {
    if (direction == "east") return EAST;
    if (direction == "south") return SOUTH;
    if (direction == "west") return WEST;
    if (direction == "north") return NORTH;
    cout << "Error: Direction "<<direction<<" is not recognized!"<<endl;
    throw 9;
}
bool judgevaild(const point_t &new_point, const grid_t & grid) {
    return !(new_point.r >= (int) grid.height || new_point.r < 0 || new_point.c >= (int) grid.width || new_point.c < 0);
}
bool ifocuppy(const point_t &adjp,const grid_t & grid) {
    return judgevaild(adjp,grid) && (grid.squares[adjp.r][adjp.c] != NULL);
}

void printGrid(const grid_t &grid) {
    //cout << grid.height << " " << grid.width;
    for (unsigned int i = 0; i < grid.height; i++) {
        for (unsigned int j = 0; j < grid.width; j++)  { 
            if (grid.squares[i][j] == NULL) 
                cout << "____ ";
            else 
                cout << ((grid.squares[i][j]->species)->name).substr(0, 2) << "_" << directShortName[grid.squares[i][j]->direction] << " ";}
    cout << endl;
    }
}

point_t adjacentPoint(point_t pt, direction_t dir) {
    point_t ans = pt;
    if (dir == EAST) ans.c++;
    if (dir == WEST) ans.c--;
    if (dir == SOUTH) ans.r++;
    if (dir == NORTH) ans.r--;
    return ans;
}

direction_t leftFrom(direction_t dir){
    return encode_direction(directName[((int)dir+3) %4]);
}

direction_t rightFrom(direction_t dir){
    return encode_direction(directName[((int)dir+1) %4]);
}

instruction_t getInstruction(const creature_t &creature){
    return creature.species->program[creature.programID];
}

creature_t *getCreature(const grid_t &grid, point_t location){
    return grid.squares[location.r][location.c];
}

bool initWorld(world_t &world, const string &speciesFile, const string &creaturesFile) {
    
    try {
        world.numCreatures=0;
        world.numSpecies=0;

        grid_t grid;
        ifstream iwFile,isFile,icFile;
        string folder_name,species_name,creature_name,direction,line;


        isFile.open(speciesFile);
        if (!isFile) {
            throw speciesFile;
        }
        getline(isFile,folder_name);

        while (getline(isFile,species_name)) {
            icFile.open(folder_name+"/"+species_name);
            if (!icFile) throw folder_name+"/"+species_name;
            species_t new_species;
            new_species.name = species_name;
            new_species.programSize=0;

            instruction_t instruction;
            string instruction_s;
            istringstream iStream;
            while (getline(icFile, line)) {
                
                iStream.clear();
                iStream.str(line);
                if (line == "") break;
                iStream >> instruction_s;
                if (instruction_s == "ifempty" || instruction_s == "ifwall" || instruction_s == "ifsame" || instruction_s == "ifenemy" || instruction_s == "go") {
                    iStream >> instruction.address;
                }
                else if (!(instruction_s == "hop" || instruction_s == "left" || instruction_s == "right" || instruction_s == "infect"))  {
                    cout <<  "Error: Instruction " << instruction_s << " is not recognized!";
                    throw 6;
                }
                instruction.op = encode_instruction(instruction_s);
                if (new_species.programSize+1 > MAXPROGRAM) throw new_species;
                new_species.program[new_species.programSize++] = instruction;
            }
            
            iStream.clear();
            icFile.close();
            if (world.numSpecies+1 > MAXSPECIES) throw 4;
            world.species[world.numSpecies++] = new_species;
        }
        isFile.close();
        iwFile.open(creaturesFile);
        if (!iwFile) throw creaturesFile;
        iwFile >> grid.height;
        if (grid.height > MAXHEIGHT || grid.height < 1) throw 10;
        iwFile >> grid.width;
        if (grid.width > MAXWIDTH || grid.width <1) throw 11;
        for (unsigned int i=0;i< grid.height;i++) 
            for (unsigned int j=0;j< grid.width;j++)
                grid.squares[i][j] = NULL;


        iwFile >> creature_name;
        creature_t new_creature;
        point_t new_point;
        while (iwFile) {
            iwFile >> direction;
            iwFile >> new_point.r;
            iwFile >> new_point.c;
            if (!judgevaild(new_point,grid)) {
                cout << "Error: Creature (" << creature_name << " " << direction << " " << new_point.r;
                cout << " " << new_point.c << ") is out of bound!"<<endl;
                cout << "The grid size is "<<grid.height <<"-by-"<<grid.width<< "." << endl;
                throw 12;
            } 
            new_creature.location = new_point;
            new_creature.direction = encode_direction(direction);
            new_creature.programID = 0;
            new_creature.species = NULL;
            for (unsigned int i=0;i<world.numSpecies;i++) 
                if (world.species[i].name == creature_name) {
                    new_creature.species = &(world.species[i]);
                    break;
                }
            if (new_creature.species == NULL) {
                cout << "Error: Species "<< creature_name <<" not found!" <<endl;
                throw 8;
            }
            if (world.numCreatures +1 > MAXCREATURES) throw new_creature;
            world.creatures[world.numCreatures++] = new_creature;
            if (grid.squares[new_point.r][new_point.c] != NULL) {
                creature_t old_creature = *(grid.squares[new_point.r][new_point.c]);
                cout << "Error: Creature (" << new_creature.species->name << " " << directName[new_creature.direction] << " " << new_point.r << " " << new_point.c << ")";
                cout << " overlaps with creature (" << old_creature.species->name << " " << directName[old_creature.direction] << " " << new_point.r << " " << new_point.c << ")!"<<endl;
                throw 13;
                //cout << "Error: Creature (<SP1> <DIR1> <R> <C>) overlaps with creature (<SP2> <DIR2> <R> <C>)! "
            }
            else grid.squares[new_point.r][new_point.c] = & (world.creatures[world.numCreatures-1] );

            iwFile >> creature_name;
        }
        world.grid=grid;
        iwFile.close();
    }
    catch (string warning){
        cout << "Error: Cannot open file " << warning <<"!" <<endl;
        return false;
    } catch (species_t new_species) {
        cout << "Error: Too many instructions for species " << new_species.name <<"!"<<endl;
        cout << "Maximal number of instructions is " << MAXPROGRAM << "."<<endl;
        return false;
    } catch (creature_t new_creature) {
        cout << "Error: Too many creatures!" << endl << "Maximal number of creatures is "<< MAXCREATURES << "." << endl;
        return false;
    } catch (int category) {
        if (category == 4)  cout << "Error: Too many species!" << endl << "Maximal number of species is " << MAXSPECIES << "." <<endl;
        if (category == 10) cout << "Error: The grid height is illegal!" <<endl;
        if (category == 11) cout << "Error: The grid width is illegal!" << endl;
        return false;
    }
    return true;
}

void simulateCreature(creature_t &creature, grid_t &grid, bool verbose){
    //Creature (hop east 2 0) takes action: 
    cout << "Creature (" << creature.species->name << " " << directName[creature.direction] << " ";
    cout << creature.location.r << " " << creature.location.c << ") takes action:";
    if (verbose) cout<<endl;
    else cout << " ";
    instruction_t instruction;
    while (true) {
            instruction = getInstruction(creature);
            int n = (creature.species->programSize);
            creature.programID = (creature.programID + 1) % n;
            if (verbose) cout << "Instruction " << (creature.programID + n -1 )% n + 1 << ": " << opName[instruction.op] ;
            point_t adjp = adjacentPoint(creature.location, creature.direction);
            creature_t* target_creature = getCreature(grid, adjp);
            if (instruction.op == HOP ) {
                if (!judgevaild(adjp,grid) || ifocuppy(adjp,grid)) {if (verbose) cout << endl; break;}
                grid.squares[creature.location.r][creature.location.c] = NULL;
                creature.location = adjp;
                grid.squares[adjp.r][adjp.c] = &creature;
                if (verbose) cout << endl;
                break;
            }
            if (instruction.op == LEFT) {creature.direction=leftFrom(creature.direction);if (verbose) cout << endl;break;}
            if (instruction.op == RIGHT) {creature.direction=rightFrom(creature.direction);if (verbose) cout << endl;break;}
            if (instruction.op == INFECT) {
                if (!judgevaild(adjp,grid) || !ifocuppy(adjp,grid)) {if (verbose) cout << endl;break;}
                if (target_creature == NULL || target_creature->species->name == creature.species->name) {if (verbose) cout << endl;break;}
                target_creature->species = creature.species;
                target_creature->programID = 0;
                if (verbose) cout << endl;
                break;
            }
            if (verbose) cout << " " << instruction.address << endl;
            if ((instruction.op == IFEMPTY && judgevaild(adjp,grid) && !ifocuppy(adjp,grid)) ||
                (instruction.op == IFWALL && !judgevaild(adjp,grid)) ||
                (instruction.op == IFSAME && judgevaild(adjp,grid) && target_creature != NULL && (target_creature->species->name) == (creature.species->name)) ||
                (instruction.op == IFENEMY && judgevaild(adjp,grid) && target_creature != NULL && (target_creature->species->name) != (creature.species->name)) || 
                (instruction.op == GO))  {
                    creature.programID = instruction.address-1;
                    continue;
                }
        }
    if (!verbose) cout << opName[instruction.op] <<endl;
    if (verbose) printGrid(grid);
}

