#ifndef maze_h
#define maze_h

#include<iostream>
#include<sstream>

using namespace std;

#include<vector>
#include "mazeNode.h"
#include "disjointSets.h"
#include "stack.h"
#include "queue.h"
#include<fstream>
#include<ctime>

class maze
{
public:
	maze(int size);
	maze(vector<mazeNode*>* newMaze);
	~maze();

	void printMaze();
	void printTraversal(stack<int>* Traversal, string method);

	stack<int>* bfs();
	stack<int>*dfs();
	
	bool connected();
	int getRooms();

	void fileWrite(string text);
	void exportMaze();

private:
	bool deadEnd(mazeNode* currNode);
	vector<mazeNode*>* mazeRoom;
	mazeNode* mazeStart;
	int mazeRooms;
	int mazeWidth;
	ofstream output;
	bool large;
};

#endif