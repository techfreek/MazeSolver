#include "disjointSets.h"

disjointSet::disjointSet(int nodes)
{
	Vnodes = nodes; //total nodes in the set
	setVector = new vector<int>(nodes);
	for(int i = 0; i < nodes; i++)
	{
		setVector->at(i) = -1; //marks each as negative 1
	}
}

disjointSet::~disjointSet()
{
	delete setVector;
}

int disjointSet::find(int target, int iterations)
{
	if(setVector->at(target) < 0) //if the value at target is less than 1, then we can simply return the target
		return target;
	else if(iterations > (Vnodes + 1)) //this is used to ensure infinite loops cannot occur. they are set to terminate at a certain point
		return target; //this point is one larger than the size of the set (meaning 1 more than should be possible)
	else
	{
		int tempInt = setVector->at(target); //seperating the values makes it easier to debug
		return find(tempInt, iterations + 1);
	}
}

int disjointSet::findRoot()
{
	for(int i = 0; i < setVector->capacity(); i++)
	{//finds the root of an element
		if(setVector->at(i) <= -1)
			return i;
	}
	return NULL;
}

bool disjointSet::setUnion(int root, int child, int uniontype)
{
	/*

	*/
	if(uniontype == 0) //I did this so it could be reused a lot easier
		return basicUnion(root, child);
	if(uniontype == 1) //however I didn't implement/test these unions
		return heightUnion(root, child);
	if(uniontype == 2)
		return sizeUnion(root, child);
	else
		return false;
}

int disjointSet::connected()
{
	/*
		this function counts how many values are less than zero, to see how many indivual sets exist
	*/
	int i = 0,
		roots = 0,
		first = -1;

	while(i < Vnodes) 
	{
		if(setVector->at(i) < 0)
		{
			roots++;
			if(first == -1)
				first = i;
			if(roots >= 1)
				return first;
		}
		i++;
	}
	return -1;
}

bool disjointSet::connected(int randInt, int genInt)
{
	/*
		designed for basic union, redesign with other union types
		this is designed to do an enhanced find(randInt) == find(genInt), but it is bugged, and overcomplicated
	*/
	int findRand = find(randInt),
		findGen = find(genInt),
		vAtRand = setVector->at(randInt),
		vAtGen = setVector->at(genInt);
	if(vAtRand == genInt)
		return true;
	if(vAtGen <= - 1)
		return false;
	if(findRand == findGen)
		return true;
	return false;		
}

bool disjointSet::basicUnion(int a, int b)
{ //sets the value at b equal to a
	setVector->at(b) = a;
	return true;
}

bool disjointSet::sizeUnion(int a, int b)
{ //this algorithm needs to be tested (and probably re-written)
	if(setVector[b] < setVector[a])
		setVector->at(a) = b;
	else
	{
		if(setVector[a] == setVector[b])
			setVector->at(a)--;
		setVector->at(b) = a;
	}
	return true;
}

bool disjointSet::heightUnion(int a, int b)
{ //this algorithm needs to be tested (and probably re-written)
	if(setVector[b] < setVector[a])
		setVector->at(a) = b;
	else
	{
		if(setVector[a] == setVector[b])
			setVector->at(a)--;
		setVector->at(b) = a;
	}
	return true;
}

void disjointSet::printSet(int target)
{ //I forgot how/why i implemented it
	if(setVector->at(target) < 0)
	{
		cout << target << endl;
	}
	else
	{
		int tempInt = setVector->at(target);
		cout << tempInt;
		printSet(tempInt);
	}
}

stack<int>* disjointSet::toStack(int target, stack<int>* newStack)
{//takes each element and pushes it to a stack, and works almost exactly like the find(x) function, but adds a stack into the mix
	if(setVector->at(target) < 0)
	{
		newStack->push(target);
		return newStack;
	}
	else
	{
		int tempInt = setVector->at(target);
		newStack->push(target);
		toStack(tempInt, newStack);
	}
	return newStack;
}

int disjointSet::unionCount()
{ //same as connected(), I guess I implemented it in two places, need to optimize disjointSets
	int sum = 0;
	for(int i = 0; i < setVector->capacity(); i++)
	{
		if(setVector->at(i) != -1)
			sum++;
	}
	count = sum;
	return sum;
}

int disjointSet::setAt(int target)
{ //returns the value at target in setVector
	return setVector->at(target);
}

bool disjointSet::findLoop()
{ //checks for loops in the set, was not used in final code, but was used in previous versions of the genMaze()
	vector<int> search(setVector->capacity());
	int tempInt = 0;

	for(int i = 0; i < setVector->capacity(); i++)
	{
		tempInt = setVector->at(i);
		while(tempInt > 0)
		{
			search.at(tempInt)++;
			tempInt = setVector->at(tempInt);
			if(search.at(tempInt) > 1)
				return true;
		}
		search.clear();
	}
}

bool disjointSet::findLoop(int root, int child, int uniontype)
{ //checks for loops in the set, was not used in final code, but was used in previous versions of the genMaze()
	vector<int>* tempSetVect = new vector<int>(setVector->capacity());
	vector<int> search(setVector->capacity());
	int tempInt = 0;
	if(unionCount() == 0)
		return false;
	for(int i = 0; i < setVector->capacity(); i++)
	{
		tempSetVect->at(i) = setVector->at(i);
	}
	tempSetVect->at(child) = root;

	tempInt = tempSetVect->at(child);
	while(tempInt > 0)
	{
		search.at(tempInt)++;
		if(search.at(tempInt) > 1)
			return true;
		tempInt = tempSetVect->at(tempInt);
	}
	search.clear();
	return false;	
}

int disjointSet::pointedAt(int target)
{ //i think this is another implementation of findRoot()
	int num = 0;
	for(int i = 0; i < setVector->capacity(); i++)
	{
		if(setVector->at(i) == target)
			num++;
	}
	return num;
}

int disjointSet::at(int pos)
{ //again, another implemenation of setAt, I really need to look through my code before I add another function
	int IDat = setVector->at(pos);
	return IDat;
}

bool disjointSet::complete(int ID)
{ //I really need to start commenting while I code because I forgot what this does
	if(ID == 0)
		return true;
	else if(setVector->at(ID) > 0 && setVector->at(setVector->at(ID)) == ID)
		return false;
	else if(setVector->at(ID) == -1)
		return false;
	else
		return complete(setVector->at(ID));
}

vector<int>* disjointSet::linked(int node)
{ //this finds all the nodes that are connected to node in any way, either node pointing at them, or the other node pointing at the passed in node
	vector<int>* linkedNodes = new vector<int>();
	vector<int>* toCheck = new vector<int>();
	int tempInt = 0,
		currInt = 0;
	toCheck->push_back(node);
	for(int k = 0; k < Vnodes; k++)
	{
		if(setVector->at(k) == node)
			toCheck->push_back(k);
	}
	for(int j = 0; j < toCheck->capacity(); j++)
	{
		currInt = toCheck->at(j);
		do
		{
			linkedNodes->push_back(currInt);
			currInt = setVector->at(currInt);
		}while(currInt != -1);
	}
	return linkedNodes;

}