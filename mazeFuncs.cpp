#include"mazeFuncs.h"

vector<mazeNode*>* readFile(string fileName)
{
	/*
	I don't think I actually used the vector, be sure I did that because I think  need it for this function
	*/
	ifstream mazeFile(fileName); //opens file
	vector<mazeNode*>* maze; //create the vector for all the nodes
	int size = 0,
		i_rooms = 0,
		roomNum = 0,
		tempRoom = 0;
	int open = true;

	mazeNode* tempNode;
	mazeNode* currNode;
	mazeNode* connectedNode;

	string s_rooms,
		roomLine;

	if(mazeFile.is_open()) //so we dont try to read from a closed file
	{
		getline(mazeFile, s_rooms, '\n'); //get the first line which is the size of the maze
		size = stoi(s_rooms); //gets the size to be an int
		i_rooms = size * size; //calculates the total # of rooms	
		maze = new vector<mazeNode*>(i_rooms);
		do
		{ //creates a node for every element in the vector
			tempNode = new mazeNode();
			getline(mazeFile, roomLine, '\n'); //gets the line that shows the open/closed doors
			open = stoi(roomLine.substr(0, 1)); //converts 1 number at a time to a bool
			tempNode->northD = open; //then sets the door to open/closed
			open = stoi(roomLine.substr(2, 3));
			tempNode->southD = open;
			open = stoi(roomLine.substr(4, 5));
			tempNode->eastD = open;
			open = stoi(roomLine.substr(6, 7));
			tempNode->westD = open;
			tempNode->ID = roomNum;
			maze->at(roomNum) = tempNode;
			roomNum++;
		} while(!(mazeFile.eof()));
		for(int i = 0; i < i_rooms; i++)
		{
			currNode = maze->at(i); //takes every element 1x1
			if(!(currNode->northD) && (currNode->northPtr == NULL))
			{ //if the north door is open, and it is not connected to anything, we will grab the node to the north
				tempRoom = i - size; //in this case, that would be i - size
				if((tempRoom > 0)) //this is incase of the start/end nodes which have an empty pointer
				{
					connectedNode = maze->at(tempRoom);
					currNode->northPtr = connectedNode;
					connectedNode->southPtr = currNode;
				}
				else
					currNode->northPtr = NULL;
			}
			if(!(currNode->southD) && (currNode->southPtr == NULL))
			{
				tempRoom = i + size;
				if((tempRoom < i_rooms))
				{
					
					connectedNode = maze->at(tempRoom);
					currNode->southPtr = connectedNode;
					connectedNode->northPtr = currNode;
				}
				else
					currNode->southPtr = NULL;
			}
			if(!(currNode->eastD) && (currNode->eastPtr == NULL))
			{
				tempRoom = i + 1;
				if((tempRoom > 0) && (tempRoom < i_rooms)) //so we dont go out of bounds by accident
				{
					
					connectedNode = maze->at(tempRoom);
					currNode->eastPtr = connectedNode;
					connectedNode->westPtr = currNode;
				}
				else
					currNode->eastPtr = NULL;
			}
			if(!(currNode->westD) && (currNode->westPtr == NULL))
			{
				tempRoom = i - 1;
				if((tempRoom > 0) && (tempRoom < i_rooms)) 
				{
					
					connectedNode = maze->at(tempRoom);
					currNode->westPtr = connectedNode;
					connectedNode->eastPtr = currNode;
				}
				else
					currNode->westPtr = NULL;
			}
		
		}

		mazeFile.close();
		return maze;
	}
	else
	{
		cout << "Please enter a valid file name next time. " << endl;
		return NULL;
	}
}

vector<mazeNode*>* mazeGenOLD(int size)
{
	//don't forget to actually import the mazeVectorNodes into the vector
	int nodes = size * size;
	disjointSet* newMaze = new disjointSet(nodes);
	vector<mazeNode*>* mazeVector = new vector<mazeNode*>(size*size);

	int i_rooms = 0,
		roomNum = 0,
		tempRoom = 0,
		node = 0,
		genInt = 0,
		root = 0,
		loops = 0,
		cap = nodes * nodes + (2 * nodes);

	mazeNode* tempNode;

	for(int i = 0; i < mazeVector->capacity();  i++)
	{
		tempNode = new mazeNode(); //create a node for every element in the vector
		tempNode->eastD = true;
		tempNode->northD = true;
		tempNode->southD = true;
		tempNode->westD = true;
		tempNode->status = 0;
		tempNode->ID = i;
		mazeVector->at(i) = tempNode;
		if(i == (nodes - 1))
			tempNode->southD = false;
		else if(i == 0)
			tempNode->northD = false;
	}
	while(newMaze->find(0) != newMaze->find(nodes-1)) //while the first and last node are not connected
	{
		node = rand() % nodes; //generate a random int
		genInt = adjacentRoom(node, size); //find an int that is next to it
		loops++; //increase the number of loops 
		if((newMaze->find(node) != newMaze->find(genInt)) && (newMaze->at(genInt) < 0)) //make sure they are not already connected
		{ //then check if genInt has already been mapped from
			formatNodes(mazeVector->at(node), mazeVector->at(genInt), size); //configures the nodes in the mazeVector so they point to eachother
			newMaze->setUnion(node, genInt);//union them
		}
		if(loops > (cap)) //so we don't encounter an infinite loop
		{
			delete newMaze; //delete irrelevant data
			delete mazeVector;
			return NULL;
		}
		
	}
	delete newMaze;
	return mazeVector;
}

vector<mazeNode*>* mazeGen(int size, clock_t genStart)
{
	int nodes = size * size;
	disjointSet* newMaze = new disjointSet(nodes);
	vector<mazeNode*>* mazeVector = new vector<mazeNode*>(size*size);
	maze* tempMaze = NULL;

	bool complete = true,
		connected = true;

	int i_rooms = 0,
		roomNum = 0,
		tempRoom = 0,
		timer = 0,
		node = 0,
		genInt = 0,
		root = 0,
		loops = 0,
		offset = 1,
		minLoops = nodes,
		connection = 0,
		cap = 3 * nodes;

	mazeNode* tempNode;

	for(int i = 0; i < mazeVector->capacity();  i++)
	{
		tempNode = new mazeNode(); //create a node for every element in the vector
		tempNode->eastD = true;
		tempNode->northD = true;
		tempNode->southD = true;
		tempNode->westD = true;
		tempNode->status = 0;
		tempNode->ID = i;
		mazeVector->at(i) = tempNode;
		if(i == (nodes - 1))
			tempNode->southD = false;
		else if(i == 0)
			tempNode->northD = false;
	}
	
	for(; offset < size; offset++)
	{
		for(node = 0; node < nodes; node += offset)
		{
			genInt = adjacentRoom(node, size); //find an int that is next to it
			connection = relationship(node, genInt, size);
			connected = connectedNodes(mazeVector->at(node), connection);
			if(connected) //make sure they are not already complete
			{ //then check if genInt has already been mapped from
				formatNodes(mazeVector->at(node), mazeVector->at(genInt), size); //configures the nodes in the mazeVector so they point to eachother
			}
		}
	}

	/*tempMaze = new maze(mazeVector);
	tempMaze->printMaze();
	complete = tempMaze->connected();
	system("pause");*/

	do{
		timer = (clock() - genStart)/CLOCKS_PER_SEC;
		cout << "\r" << timer << flush;
		if(loops > 1)
			delete tempMaze;
		node = rand() % nodes; //generate a random int
		genInt = adjacentRoom(node, size); //find an int that is next to it
		loops++; //increase the number of loops 
		connection = relationship(node, genInt, size);

		connected = connectedNodes(mazeVector->at(node), connection);
		
		if(connected) //make sure they are not already complete
		{ //then check if genInt has already been mapped from
			formatNodes(mazeVector->at(node), mazeVector->at(genInt), size); //configures the nodes in the mazeVector so they point to eachother
		}

		if(loops > cap) //so we don't encounter an infinite loop
		{
			delete newMaze; //delete irrelevant data
			delete mazeVector;
			return NULL;
		} 

		
	tempMaze = new maze(mazeVector);
	//tempMaze->printMaze();
	complete = tempMaze->connected();
	//system("pause");
		
	}while(!complete); //while the first and last node are not complete
	delete newMaze;
	return mazeVector;
}

int adjacentRoom(int currRoom, int size)
{ //this will find a random room that is adjacent to the current on
	int xyshift = 0,
		xPos = currRoom % size,
		yPos = currRoom / size,
		shift = 0,
		genInt = 0,
		totalRooms = size * size;
	
	do {
		xyshift = rand() % 2;
		shift = rand() % 2;	
		if(xyshift == 0)
		{ //shift on x axis
			if(shift)
			{//shift right
				if(xPos == size - 1)
					genInt = -1; //forces it to scan again
				else
					genInt = currRoom + 1;	
			}
			else
			{ //shift left
				if(xPos == 0)
					genInt = -1;
				else
					genInt = currRoom - 1;
			}
		}
		else
		{//shift on y axis
			if(shift)
			{ //shift up
				if(yPos == 0) //we know if something is on the top row, and we want to shift up, that we will run into errors
					genInt = -1; //so we just set it to a value so it scans again
				else
					genInt = currRoom - size;
			}
			else
			{//shift down
				if(yPos == (size - 1))
					genInt = -1; 
				else
					genInt = currRoom + size;
			}
		}
	}while((genInt >= totalRooms || genInt < 0)); //this ensures it is in the correct range
	return genInt;
}

bool connectedNodes(mazeNode* currNode, int connection)
{
	bool connected = false;
	if(connection == 1)
	{
		if(currNode->southD)
			connected = true;
		else
			connected = false;
	}
	else if(connection == 2)
	{
	if(currNode->northD)
			connected = true;
		else
			connected = false;
	}
	else if(connection == 3)
	{
		if(currNode->westD)
			connected = true;
		else
			connected = false;

	}else if(connection == 4)
	{
		if(currNode->eastD)
			connected = true;
		else
			connected = false;
	}
	return connected;
}

int relationship(int currRoom, int nextRoom, int size)
{ //this is all in relation to the current room
	/*
		Return values and their meaning
		1 - North
		2 - South
		3 - East
		4 - West
	*/
	int currRoomCol = 0,
		currRoomRow = 0,
		nextRoomCol = 0,
		nextRoomRow = 0;

	currRoomCol = currRoom % size; //gets x position
	nextRoomCol = nextRoom % size;

	currRoomRow = int(currRoom) / size; //gets y position
	nextRoomRow = int(nextRoom) / size;
	//works on the idea that two nodes (since they SHOULD be chosen properly) will have atleast the same line or column in common
	if((currRoomRow - 1) == nextRoomRow) //so we just do a shift on one of the other elements to see where they line up
		return 1;
	else if((currRoomRow + 1) == nextRoomRow)
		return 2;
	else if((currRoomCol + 1) == nextRoomCol)
		return 3;
	else if((currRoomCol - 1) == nextRoomCol)
		return 4;
	return 0;
}

bool formatNodes(mazeNode* currNode, mazeNode* connectedNode, int size)
{
	int roomRelationship = relationship(currNode->ID, connectedNode->ID, size); //get relationship
	if(roomRelationship == 1)
	{ //set pointers as such, so open doors, and adjust pointers
		currNode->northD = false;
		currNode->northPtr = connectedNode;
		connectedNode->southD = false;
		connectedNode->southPtr = currNode;
	}
	else if(roomRelationship == 2)
	{
		currNode->southD = false;
		currNode->southPtr = connectedNode;
		connectedNode->northD = false;
		connectedNode->northPtr = currNode;
	}
	else if(roomRelationship == 3)
	{
		currNode->eastD = false;
		currNode->eastPtr = connectedNode;
		connectedNode->westD = false;
		connectedNode->westPtr = currNode;
	}
	else if(roomRelationship == 4)
	{
		currNode->westD = false;
		currNode->westPtr = connectedNode;
		connectedNode->eastD = false;
		connectedNode->eastPtr = currNode;
	}
	return true;
}