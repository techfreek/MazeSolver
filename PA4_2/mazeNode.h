#ifndef mazenode_h
#define mazenode_h

#include <iostream>

class mazeNode
{
public:
	mazeNode(int key = 0);
	~mazeNode();
	bool northD;
	mazeNode* northPtr;
	bool southD;
	mazeNode* southPtr;
	bool eastD;
	mazeNode* eastPtr;
	bool westD;
	mazeNode* westPtr;
	int ID;
	int status; // 0 - unvisited; 1 - inspected; 2 - visited
};

#endif