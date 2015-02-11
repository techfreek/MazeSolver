#ifndef disjointsets_h
#define disjointsets_h

#include <iostream>
#include <vector>
#include "stack.h"

using namespace std;

class disjointSet :public List<int>
{
public:
	disjointSet(int nodes);
	~disjointSet();

	int at(int pos);
	int find(int target, int iterations = 0);
	int findRoot();

	bool findLoop();
	bool findLoop(int root, int child, int uniontype = 0);
	vector<int>* linked(int node);

	int pointedAt(int target);

	void printSet(int target);
	stack<int>* toStack(int target, stack<int>* newStack);

	int setAt(int target);

	bool setUnion(int root, int child, int uniontype = 0);

	int connected();
	bool connected(int randInt, int genInt);
	bool complete(int ID);

	int unionCount();

private:
	bool basicUnion(int a, int b);
	bool sizeUnion(int a, int b);
	bool heightUnion(int a, int b);

	vector<int>* setVector;
	int Vnodes;
	int count;
};



#endif