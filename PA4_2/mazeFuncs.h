#ifndef mazefuncs_h
#define mazefuncs_h

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>
#include <time.h>
#include "maze.h"
#include "disjointSets.h"
#include "mazeNode.h"

using namespace std;

vector<mazeNode*>* readFile(string fileName);
vector<mazeNode*>* mazeGen(int size, clock_t genStart);
vector<mazeNode*>* mazeGenOLD(int size);
int adjacentRoom(int currRoom, int size);
bool connectedNodes(mazeNode* currNode, int connection);
int relationship(int currRoom, int nextRoom, int size);
bool formatNodes(mazeNode* currNode, mazeNode* connectedNode, int size);

#endif