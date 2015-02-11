#include "maze.h"

maze::maze(int size)
{
	mazeWidth = size; //for future reference
	mazeRoom = new vector<mazeNode*>(size * size);//creates maze that we will later fill, however, this constructor is never used
}

maze::maze(vector<mazeNode*>* newMaze)
{
	mazeRooms = newMaze->capacity(); //counts how many rooms total there are
	mazeWidth = sqrt(double(newMaze->capacity())); //gets the dimension in either direction 
	mazeRoom = newMaze; //use the generated maze vector as the vector in the class
	mazeStart = mazeRoom->at(0); //not use
}

maze::~maze()
{
	mazeStart = NULL;
	output.close();
}

void maze::printMaze()
{
	/*
	Works by printing the doors on the top of the maze
	then goes layer by layer printing the left(west) and bottom (south) walls
	then prints the right(east) wall and ends the line
	*/
	int k = 0,
		j = 0,
		count = 0;
	mazeNode* tempNode;
	bool file = false;
	if(mazeWidth > 40)
		file = true;
	if(!file)
	{
		
		cout << "Your Maze: " << endl;
		cout << " ";

		for(int i = 0; i < mazeWidth; i++)
		{ //prints off the top row nodes by looking if the north pointer of the top node is closed, if so, print a "door" there
			if(mazeRoom->at(i)->northD)
				cout << "_ ";
			else //if not, put a gap
				cout << "  ";
		}
		cout << endl;
		for(int i = 0; i < mazeWidth; i++)
		{
			for(j = 0; j < mazeWidth; j++)
			{
				tempNode = mazeRoom->at(count); //goes line by line looking at the nodes
				if(tempNode->westD)
				{ //prints off | if the left wall is there, doesn't need to check both because the neighboring nodes would be in agreement
					cout << "|";
				}
				else
				{
					cout << " ";
				}
				if(tempNode->southD)
				{ //also checks floor so it looks more compact
					cout << "_";
				}
				else
				{
					cout << " ";
				}
				count++;
			}
			cout << "|" << endl; //prints out the right most wall at the end of a line
		}
		cout << endl << endl;
	}
	else
	{
		// current datetime based on current system
		time_t now = time(0);
   
		// convert now to string form
		string datetime= ctime(&now);

		string text = "Maze.txt";
		string location = "\Mazes\\";
		string filename;
		char* tempchar =  new char();
		
		itoa(mazeWidth, tempchar, 10);
		filename.append(location);
		filename.append(string(tempchar));
		filename.append("_");
		filename.append(datetime);
		filename.append(text);
		filename.erase((filename.find_first_of("_") + 1), 4);
		for(int i = 0; i < 3; i++)
		{
			filename.replace(filename.find_first_of(" "), 1, "_");
		}
		
		for(int i = 0; i < 2; i++)
		{
			filename.replace(filename.find_first_of(":"), 1, "_");
		}
		filename.erase((filename.length() - 9), 1);

		output.open(filename);

		cout << "Maze saved to file " << filename << endl;

		output << mazeWidth << " x " << mazeWidth << " maze. Generated on: " << datetime << endl;

		output << " ";

		for(int i = 0; i < mazeWidth; i++)
		{ //prints off the top row nodes by looking if the north pointer of the top node is closed, if so, print a "door" there
			if(mazeRoom->at(i)->northD)
				output << "_ ";
			else //if not, put a gap
				output << "  ";
		}
		output << endl;
		for(int i = 0; i < mazeWidth; i++)
		{
			for(j = 0; j < mazeWidth; j++)
			{
				tempNode = mazeRoom->at(count); //goes line by line looking at the nodes
				if(tempNode->westD)
				{ //prints off | if the left wall is there, doesn't need to check both because the neighboring nodes would be in agreement
					output << "|";
				}
				else
				{
					output << " ";
				}
				if(tempNode->southD)
				{ //also checks floor so it looks more compact
					output << "_";
				}
				else
				{
					output << " ";
				}
				count++;
			}
			output << "|" << endl; //prints out the right most wall at the end of a line
		}
		output << endl << endl;
	}

}

void maze::fileWrite(string text)
{
	output << text << endl;
}

void maze::printTraversal(stack<int>* Traversal, string Method)
{
	/*
	This works by printing the traversal
	then by making a 2d vector to whether or not the traversal passed by that point
	then it goes layer by layer printing the 2d vector
	it does this by checking if the node was used (bool integers) then if so it prints an X, if not, a space
	*/
	
	bool file = false;
	if(mazeWidth > 40)
		file = true;

	int mazeID = 0,
		count = 0;

	vector<bool> mazeVect(mazeRooms);

	if(!file)
	{
		while(!Traversal->isEmpty())
		{ 
			mazeID = Traversal->pop();
			mazeVect.at(mazeID) = true; //edits the maze vector so only the accessed nodes are marked as true
		}
		for(int i = 0; i < mazeWidth; i++)
		{
			for(int j = 0; j < mazeWidth; j++)
			{
				if(mazeVect.at(count))
				{ //so then we go line by line looking at if that node had been accessed, if so, then we say that it is
					cout << "X ";
				}
				else
				{// if not, we place a space
					cout << "  ";
				}

				count++; //so we can access the proper node
			}
			cout << endl;
		}
		cout << endl;
	}
	else
	{
		cout << "Writing traversal to file..." << endl;
		output << Method << " Traversal: " << endl << endl;

		while(!Traversal->isEmpty())
		{ 
			mazeID = Traversal->pop();
			mazeVect.at(mazeID) = true; //edits the maze vector so only the accessed nodes are marked as true
		}
		for(int i = 0; i < mazeWidth; i++)
		{
			for(int j = 0; j < mazeWidth; j++)
			{
				if(mazeVect.at(count))
				{ //so then we go line by line looking at if that node had been accessed, if so, then we say that it is
					output << "X ";
				}
				else
				{// if not, we place a space
					output << "  ";
				}

				count++; //so we can access the proper node
			}
			output << endl;
		}
		output << endl;
	}
}

stack<int>* maze::bfs()
{
	/*
		currently, this grabs the starting room, then inputs all the IDs to the traversal
		then it goes into a loop where that process continues
		needs logic to know if it reaches a deadend, something like if all doors are closed, then pop(burn) a node from the stack
		consider rearranging how nodes are accessed such that the only nodes in the stack are those that are used? so it would flow as
		west east south north. consider alternatives to this first

		maybe look into using a disjoint set to see keep track of traversal, my current method is not useful in order to get the overall output
		of the traversal to work. or maybe have 2 stacks such that one is the nodes needed to visit, and the other is the visited nodes such that
		we pop as we go back and push as we go forward. i actually like that idea
	*/
	disjointSet* setTraversal = new disjointSet(mazeWidth * mazeWidth); //creates new disjoint set so we can use a find like operations to find the final traversal
	queue<int>* tempQ = NULL;
	queue<int>* nodesToVisit = new queue<int>();
	queue<int>* nextToVisit = NULL;

	stack<int>* traversal = new stack<int>(); //fill this later with the results from setTraversal
	stack<int>* accessed = new stack<int>();

	bool end = false; //to know when we found the last element
	
	if(mazeRoom->at(0)->status != 0)
	{
		for(int m = 0; m < mazeRoom->capacity(); m++)
		{ //all nodes are marked in DFS and BFS 
			mazeRoom->at(m)->status = 0;
		} //incase DFS ran first
	}
	mazeNode* currentNode = mazeRoom->at(0); //sets current node to the first node
	mazeRoom->at(0)->status = 2; //sets its status to 2 (accessed)
	accessed->push(currentNode->ID); //marks that it has been accessed

	if(!(currentNode->southD)  && (currentNode->southPtr != NULL))
	{
		nodesToVisit->enqueue(currentNode->southPtr->ID); //marks that it needs to be checks for the traversal
		currentNode->southPtr->status = 1; //marks that it has been viewed
		setTraversal->setUnion(0, currentNode->southPtr->ID); //unions the nodes so we can later back track to view what the traversal was
		accessed->push(currentNode->southPtr->ID); //mark it has been accessed so we can see all the nodes we have accessed later on
	}
	if(!(currentNode->eastD) && (currentNode->eastPtr != NULL))
	{
		nodesToVisit->enqueue(currentNode->eastPtr->ID);
		currentNode->eastPtr->status = 1;
		setTraversal->setUnion(0, currentNode->eastPtr->ID);
		accessed->push(currentNode->eastPtr->ID);
	}
	nextToVisit = new queue<int>(); //creates a new queue because we will look through each element in nodesToVisit to look for nodes to put into
	//nextToVisit
	do	{
		while(!nodesToVisit->isEmpty() && !end) //while nodesToVisit is not empty and its not the end, end is only marked when we reach 
		{//ID = (mazeRooms-1). when nodesToVisit is empty, that means that we have finished checking the nodes at that distance from the root,
			//now it is time to move one out
			currentNode = mazeRoom->at(nodesToVisit->dequeue()); //deque the first element inserted
			currentNode->status = 2; //mark it as visited
			if(!currentNode->northD && currentNode->northPtr != NULL && currentNode->northPtr->status == 0)
			{
				currentNode->northPtr->status = 1;
				setTraversal->setUnion(currentNode->ID, currentNode->northPtr->ID);
				nextToVisit->enqueue(currentNode->northPtr->ID);
				accessed->push(currentNode->northPtr->ID);
				if(currentNode->northPtr->ID == (mazeRooms-1))//if its the last node, then note it
					end = true;
			}
			if(!currentNode->southD && currentNode->southPtr != NULL && currentNode->southPtr->status == 0)
			{
				currentNode->southPtr->status = 1;
				setTraversal->setUnion(currentNode->ID, currentNode->southPtr->ID);
				nextToVisit->enqueue(currentNode->southPtr->ID);
				accessed->push(currentNode->southPtr->ID);
				if(currentNode->southPtr->ID == (mazeRooms-1))
					end = true;
			}
			if(!currentNode->eastD && currentNode->eastPtr->status == 0)
			{
				currentNode->eastPtr->status = 1;
				setTraversal->setUnion(currentNode->ID, currentNode->eastPtr->ID);
				nextToVisit->enqueue(currentNode->eastPtr->ID);
				accessed->push(currentNode->eastPtr->ID);
				if(currentNode->eastPtr->ID == (mazeRooms-1))
					end = true;
			}
			if(!currentNode->westD && currentNode->westPtr->status == 0)
			{
				currentNode->westPtr->status = 1;
				setTraversal->setUnion(currentNode->ID, currentNode->westPtr->ID);
				nextToVisit->enqueue(currentNode->westPtr->ID);
				accessed->push(currentNode->westPtr->ID);
				if(currentNode->westPtr->ID == (mazeRooms-1))
					end = true;
			}
		}
		if(end)
			break; //so we dont add more nodes to the visited
		tempQ = nodesToVisit; //such that we can break it after the variable is re assigned
		nodesToVisit = nextToVisit; //set nextToVisit as the nodes we need to check next
		nextToVisit = new queue<int>(); //create a new queue
		delete tempQ;
	} while(currentNode->ID != ((mazeWidth * mazeWidth) -1 ));

	//accessed->push(mazeRooms-1);
	//cout << "Rooms visited by BFS: ";
	//accessed->reverseStack(); //my stack is in the correct order, but the Programming Project page, it wants it in reverse
	//accessed->printStack(); //print

	//cout << "This is the path  (in reverse): ";
	setTraversal->toStack((mazeRooms -1), traversal); //converts the disjoint set traversal to a stack in a kind of find() type function
	traversal->reverseStack(); //as before, reverse the stack
	//traversal->printStack();

	
	printTraversal(traversal, "Breadth First Search");
	

	delete setTraversal;
	delete nextToVisit;
	delete accessed;
	delete nodesToVisit;

	return traversal;
}

stack<int>* maze::dfs()
	{ 
	/*
		Start this, remember to use a trianary tree or a quadrinary tree to store the 
		point in addition to a parent pointer, so we can work our way back up maybe consider a disjoint
		set with simple union, however this would mean a node could only be accessed once, but this could be to our advantage

		read nodes to next nodes, then input those to disjoint set, then move nextNode vector to curretNodes, and delete old current nodes, then
		create a new nextNode vector with 3x the size and repeat
	*/
	stack<int>* tempQ = NULL;
	stack<int>* nodesToVisit = new stack<int>();

	disjointSet* traversal = new disjointSet(mazeWidth * mazeWidth);
	stack<int>* newTraversal = new stack<int>();
	stack<int>* finalTraversal = new stack<int>();
	stack<int>* accessedNodes = new stack<int>();
	
	mazeNode* tempNode;

	if(mazeRoom->at(0)->status != 0)
	{
		for(int m = 0; m < mazeRoom->capacity(); m++)
		{
			mazeRoom->at(m)->status = 0;
		} //incase BFS ran first
	}
	mazeRoom->at(0)->status = 2;
	accessedNodes->push(mazeRoom->at(0)->ID);
	if(mazeRoom->at(0)->southD == false)
	{
		//nodesToVisit->push(mazeRoom->at(0)->southPtr->ID); //puts it into a stack, and with this implementation, we dont need to specify a size
		mazeRoom->at(0)->southPtr->status = 1; //mark viewed
		traversal->setUnion(0, mazeRoom->at(0)->southPtr->ID);
		newTraversal->push(mazeRoom->at(0)->southPtr->ID);
		//accessedNodes->push(mazeRoom->at(0)->southPtr->ID);
	}
	if(mazeRoom->at(0)->eastD == false)
	{
		//nodesToVisit->push(mazeRoom->at(0)->eastPtr->ID);
		mazeRoom->at(0)->eastPtr->status = 1;
		traversal->setUnion(0, mazeRoom->at(0)->eastPtr->ID);
		newTraversal->push(mazeRoom->at(0)->eastPtr->ID);
		//accessedNodes->push(mazeRoom->at(0)->eastPtr->ID);
	}

	tempNode = mazeRoom->at(newTraversal->pop()); //deque the first element inserted
	tempNode->status = 2; //mark it as visited

	
	do {
		if(!tempNode->northD && tempNode->northPtr != NULL && tempNode->northPtr->status == 0)
		{
			//nodesToVisit->push(tempNode->northPtr->ID);
			tempNode->northPtr->status = 1;
			traversal->setUnion(tempNode->ID, tempNode->northPtr->ID);
			newTraversal->push(tempNode->northPtr->ID);
		}
		if(!tempNode->southD && tempNode->southPtr != NULL && tempNode->southPtr->status == 0)
		{
			//nodesToVisit->push(tempNode->southPtr->ID);
			tempNode->southPtr->status = 1;
			traversal->setUnion(tempNode->ID, tempNode->southPtr->ID);
			newTraversal->push(tempNode->southPtr->ID);
		}
		if(!tempNode->eastD && tempNode->eastPtr->status == 0)
		{
			//nodesToVisit->push(tempNode->eastPtr->ID);
			tempNode->eastPtr->status = 1;
			traversal->setUnion(tempNode->ID, tempNode->eastPtr->ID);
			newTraversal->push(tempNode->eastPtr->ID);
		}
		if(!tempNode->westD && tempNode->westPtr->status == 0)
		{
			//nodesToVisit->push(tempNode->westPtr->ID);
			tempNode->westPtr->status = 1;
			traversal->setUnion(tempNode->ID, tempNode->westPtr->ID);
			newTraversal->push(tempNode->westPtr->ID);
		}
		if(deadEnd(tempNode))
		{ //deadend meaning that no other node can be accessed
			accessedNodes->push(tempNode->ID); //store te element that is at the deadend
			//newTraversal->pop(); // burns the current node off the traversal
			do{
				int tempInt = newTraversal->pop();
				tempNode = mazeRoom->at(tempInt);
				tempNode->status = 2;
			}while(deadEnd(tempNode));
		}
		else
		{
			accessedNodes->push(tempNode->ID); //store node we visited
			tempNode = mazeRoom->at(newTraversal->pop()); //deque the first element inserted
			tempNode->status = 2; //mark it as visited
		}
	} while(tempNode->ID != mazeRooms - 1);
	accessedNodes->push(mazeRooms - 1);
	//cout << "Rooms visited by DFS: ";
	//accessedNodes->reverseStack();
	//accessedNodes->printStack();

	//cout << "This is the path  (in reverse): ";
	traversal->toStack((mazeRooms -1), finalTraversal);
	finalTraversal->reverseStack();
	//finalTraversal->printStack();

	printTraversal(finalTraversal, "Depth First Search");

	delete traversal;
	delete newTraversal;
	delete accessedNodes;

	return finalTraversal;
}

bool maze::connected()
{
		/*
		currently, this grabs the starting room, then inputs all the IDs to the traversal
		then it goes into a loop where that process continues
		needs logic to know if it reaches a deadend, something like if all doors are closed, then pop(burn) a node from the stack
		consider rearranging how nodes are accessed such that the only nodes in the stack are those that are used? so it would flow as
		west east south north. consider alternatives to this first

		maybe look into using a disjoint set to see keep track of traversal, my current method is not useful in order to get the overall output
		of the traversal to work. or maybe have 2 stacks such that one is the nodes needed to visit, and the other is the visited nodes such that
		we pop as we go back and push as we go forward. i actually like that idea
	*/
	disjointSet* setTraversal = new disjointSet(mazeWidth * mazeWidth); //creates new disjoint set so we can use a find like operations to find the final traversal
	queue<int>* tempQ = NULL;
	queue<int>* nodesToVisit = new queue<int>();
	queue<int>* nextToVisit = NULL;

	bool traversal = false;

	bool end = false; //to know when we found the last element
	
	if(mazeRoom->at(0)->status != 0)
	{
		for(int m = 0; m < mazeRoom->capacity(); m++)
		{ //all nodes are marked in DFS and BFS 
			mazeRoom->at(m)->status = 0;
		} //incase DFS ran first
	}
	mazeNode* currentNode = mazeRoom->at(0); //sets current node to the first node
	mazeRoom->at(0)->status = 2; //sets its status to 2 (accessed)

	if(!(currentNode->southD)  && (currentNode->southPtr != NULL))
	{
		nodesToVisit->enqueue(currentNode->southPtr->ID); //marks that it needs to be checks for the traversal
		currentNode->southPtr->status = 1; //marks that it has been viewed
		setTraversal->setUnion(0, currentNode->southPtr->ID); //unions the nodes so we can later back track to view what the traversal was
	}
	if(!(currentNode->eastD) && (currentNode->eastPtr != NULL))
	{
		nodesToVisit->enqueue(currentNode->eastPtr->ID);
		currentNode->eastPtr->status = 1;
		setTraversal->setUnion(0, currentNode->eastPtr->ID);
	}
	nextToVisit = new queue<int>(); //creates a new queue because we will look through each element in nodesToVisit to look for nodes to put into
	//nextToVisit
	while(!end && !nodesToVisit->isEmpty()){
		while(!nodesToVisit->isEmpty() && !end) //while nodesToVisit is not empty and its not the end, end is only marked when we reach 
		{//ID = (mazeRooms-1). when nodesToVisit is empty, that means that we have finished checking the nodes at that distance from the root,
			//now it is time to move one out
			currentNode = mazeRoom->at(nodesToVisit->dequeue()); //deque the first element inserted
			currentNode->status = 2; //mark it as visited
			if(!currentNode->northD && currentNode->northPtr != NULL && currentNode->northPtr->status == 0)
			{
				currentNode->northPtr->status = 1;
				setTraversal->setUnion(currentNode->ID, currentNode->northPtr->ID);
				nextToVisit->enqueue(currentNode->northPtr->ID);
				if(currentNode->northPtr->ID == (mazeRooms-1))//if its the last node, then note it
					end = true;
			}
			if(!currentNode->southD && currentNode->southPtr != NULL && currentNode->southPtr->status == 0)
			{
				currentNode->southPtr->status = 1;
				setTraversal->setUnion(currentNode->ID, currentNode->southPtr->ID);
				nextToVisit->enqueue(currentNode->southPtr->ID);
				if(currentNode->southPtr->ID == (mazeRooms-1))
					end = true;
			}
			if(!currentNode->eastD && currentNode->eastPtr->status == 0)
			{
				currentNode->eastPtr->status = 1;
				setTraversal->setUnion(currentNode->ID, currentNode->eastPtr->ID);
				nextToVisit->enqueue(currentNode->eastPtr->ID);
				if(currentNode->eastPtr->ID == (mazeRooms-1))
					end = true;
			}
			if(!currentNode->westD && currentNode->westPtr->status == 0)
			{
				currentNode->westPtr->status = 1;
				setTraversal->setUnion(currentNode->ID, currentNode->westPtr->ID);
				nextToVisit->enqueue(currentNode->westPtr->ID);
				if(currentNode->westPtr->ID == (mazeRooms-1))
					end = true;
			}
		}
		if(end)
		{
			traversal = true;
			break; //so we dont add more nodes to the visited
			
		}

		tempQ = nodesToVisit; //such that we can break it after the variable is re assigned
		nodesToVisit = nextToVisit; //set nextToVisit as the nodes we need to check next
		nextToVisit = new queue<int>(); //create a new queue
		delete tempQ;
	} 

	delete setTraversal;
	delete nextToVisit;
	delete nodesToVisit;

	return traversal;
}

bool maze::deadEnd(mazeNode* currNode)
{
	int count = 0;
	if(currNode->ID == mazeRooms - 1) //makes sure it is not the last element before doing anything
		return false;
	if(!currNode->northD || !currNode->southD || !currNode->eastD || !currNode->westD) //if any of them are open
	{
		if(!currNode->northD) //check each individually
		{
			if(currNode->northPtr->status == 2)
				count++; //increase counter of how many ways it can go
		}
		else //if closed, increase counter
			count++;
		if(!currNode->southD)
		{
			if(currNode->southPtr->status == 2)
				count++;
		}
		else
			count++;
		if(!currNode->eastD)
		{
			if(currNode->eastPtr->status == 2)
				count++;
		}
		else
			count++;
		if(!currNode->westD)
		{
			if(currNode->westPtr->status == 2)
				count++;
		}
		else
			count++;
		if(count >= 4) //if four or more doors are closed or the adjacent node has been accessed, then deadend
			return true;
		else
			return false;
	}
	return true; //if all are closed, we know it is in a deadend

}

int maze::getRooms()
{
	return this->mazeRooms;
}

void maze::exportMaze()
{
	char* tempchar =  new char();
	string fileName = "";
	string file = "Maze.txt";
	itoa(this->getRooms(), tempchar, 10);
	fileName.append(string(tempchar));
	fileName.append(file);
	ofstream exported;
	exported.open(fileName);
	exported << tempchar << endl;
	for(int i = 0; i < this->getRooms(); i++)
	{
		if(mazeRoom->at(i)->northD)
			exported << "1 ";
		else
			exported << "0 ";
		if(mazeRoom->at(i)->southD)
			exported << "1 ";
		else
			exported << "0 ";
		if(mazeRoom->at(i)->eastD)
			exported << "1 ";
		else
			exported << "0 ";
		if(mazeRoom->at(i)->westD)
			exported << "1 ";
		else
			exported << "0 ";
		exported << '\n';
	}
	exported.close();
}