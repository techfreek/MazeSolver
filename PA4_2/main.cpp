#include"mazeFuncs.h"
#include<time.h>
#include<iostream>
#include<string>

int main(int argc, char* argv[])
{
	srand(time(NULL));
	int arr_size = 0,
		loops = 0,
		newLoops = 0,
		cap = 500,
		intLength = 0,
		minutes = 0,
		hours = 0,
		timer = 0,
		oldTimer = 0;
	char* tempchar =  new char();
	string fileName,
		tempStr,
		arr_input,
		sInput;
	if(argv[1] != NULL)
		fileName = argv[1];
	
	maze* theMaze = NULL;
	vector<mazeNode*>* mazeVector;
	vector<mazeNode*>* mazeVectorOLD;

	double genTime = 0,
		bfsTime = 0,
		dfsTime = 0,
		totTime = 0;

	bool file = false,
		second = false,
		stop = false,
		old = false;

	clock_t tStart = NULL,
		genStart = NULL,
		dfsStart = NULL,
		bfsStart = NULL,
		oldStart = NULL,
		oldDone = NULL;
                       

cout << endl;
	do{
		 //I use a clock purely for curiosities sake
		if(second)
		{ //resets values to avoid errors
			second = false;
			loops = 0;
			file = false;
			stop = false;
			fileName.clear();
			sInput.clear();
		}
		if(fileName.empty())
		{
			cout << "What would you like to do? " << endl;
			cout << "  I - To import a maze from a file" << endl;
			cout << "  G - To generate a maze" << endl;
			cout << "  O - To generate a maze with the obsolete algorithm" << endl;
			cout << "  E - To exit " << endl << ">> ";
			getline(cin, sInput); //Input as string to avoid errors when people type the full name, instead of the character"
			if(second)
				cin.get();
		}
		
		if(tolower(sInput[0]) == 'o')
		{
			//Let's the system know to run the maze generation as the old algorithm so code doesn't have to be repeated.
			cout << "Note: This code is obsolete and no longer supported. It is slow, and can rarely produce mazes greater than 12. It is included to show the improvement since spring." << endl;
			old = true;
		}
		if(tolower(sInput[0]) == 'e')
		{	
			exit(1);
		}
		else if(tolower(sInput[0]) == 'i' || !fileName.empty())
		{
			file = true;
			if(fileName.empty())
			{
				cout << "What is the file name? ";
				cin >> fileName;
				cin.get();
			}
			genStart = tStart = clock();
			mazeVector = readFile(fileName);
			cout << "Maze rebuild time: " << double((clock() - genStart))/CLOCKS_PER_SEC << endl;
			if(mazeVector == NULL)
				theMaze = NULL;
			else
			{
				theMaze = new maze(mazeVector); //reads file, generates a maze, returns a vector, then makes the maze class
				theMaze->printMaze(); //prints maze
			}
		}
		else if(tolower(sInput[0]) == 'g' || tolower(sInput[0]) == 'o')
		{
			do{
				loops = 0;
				if(arr_size == -100)
					cout << "Please enter positive integer. " << endl;
				else if(arr_size < 2 && second) // so we dont get an incredibly tiny maze, may cause some problem
					cout << "Please enter a larger number. " << endl;
				else if(arr_size > cap) //Further optimization is required to generate larger mazes
					cout << "For the sake of your computer, please enter a number less than or equal to " << cap << "." << endl; //I should joke less in my code
				cout << "How big of a maze would you like made? ";
				cin >> arr_input;
				cin.get();
				for(intLength = 0; intLength < arr_input.size() && isdigit(arr_input.at(intLength)); intLength++); //counts length of integer at start of string
				if(intLength > 0)
					arr_size = stoi(arr_input.substr(0, intLength)); //converts said integer to an integer type
				else
					arr_size = -100; //Forces size to be re-sInputted
			}while(arr_size < 2 || arr_size > cap);
			cout << "Maze size: " << arr_size << " x " << arr_size << "; Nodes: " << arr_size * arr_size << endl;
			genStart = tStart = clock();
			cout << "Processing Time: " << endl;
			if(!old)
				cout << "\r" << (clock() - genStart)/CLOCKS_PER_SEC << flush; //Keeps a rolling clock of the time taken to generate the maze
			do{
				if(!old) //Allows the user to compare the two algorithms
					mazeVector = mazeGen(arr_size, genStart);
				else
					mazeVector = mazeGenOLD(arr_size);
				loops++; //I have noticed that random mazes can sometimes get stuck in generating, so I have learned that sometimes it is best to just restart
			}while(mazeVector == NULL && loops < arr_size);

			cout << endl;
			genTime = double(clock() - genStart)/CLOCKS_PER_SEC;

			if(loops >= arr_size)
			{ //in case it takes too long generate, it stops trying
				cout << endl << "Maze generation failed. Please try again or try a smaller maze size." << endl;
				cout << "Maze generation attempt time: " << double(genTime)/CLOCKS_PER_SEC << endl;
			}
			if(mazeVector != NULL)
			{
				theMaze = new maze(mazeVector); //if it works, then make the maze
				cout << endl;
				theMaze->printMaze();
			}
			
		}
		else
			cout << "Please enter a valid command next time." << endl;
		if(theMaze != NULL && (sInput.find("-e") > 0))
		{
			cout << "--Exporting maze for re-use--" << endl;
			theMaze->exportMaze();
		}
		if(theMaze != NULL && (sInput.find("-s") > 0))
		{
			if(sInput.find("-s") > 0)
				cout << "--Force solve--" << endl;
			if((sInput.find("-s") > 0) || sInput.length() == 1)
			{
				bfsStart = clock();
				theMaze->bfs(); //runs the bfs algorithm
				bfsTime = double((clock() - bfsStart))/CLOCKS_PER_SEC;
				cout << endl << endl;

				dfsStart = clock();
				theMaze->dfs(); //runs the dfs algorithm
				dfsTime = double((clock() - dfsStart))/CLOCKS_PER_SEC;			
			}
			if(arr_size > 40)
			{ //If the maze is wider than the command line, I export it to a file for easier readability
				
				tempStr.append("Maze Size: "); //Formats the maze size string
				itoa(arr_size, tempchar, 10);
				tempStr.append(string(tempchar));
				tempStr.append(" x ");
				tempStr.append(string(tempchar));
				tempStr.append("; Nodes: ");
				itoa((arr_size * arr_size), tempchar, 10);
				tempStr.append(string(tempchar));
				theMaze->fileWrite(tempStr);
				tempStr.clear();

				tempStr.append("Maze Generation Time: "); //Formatting the times as strings so they can be included in the file
				itoa(genTime, tempchar, 10);
				tempStr.append(string(tempchar));
				theMaze->fileWrite(tempStr);
				tempStr.clear();

				tempStr.append("BFS sort time:        ");
				itoa(bfsTime, tempchar, 10);
				tempStr.append(string(tempchar));
				theMaze->fileWrite(tempStr);
				tempStr.clear();

				tempStr.append("DFS sort time:        ");
				itoa(dfsTime, tempchar, 10);
				tempStr.append(string(tempchar));
				theMaze->fileWrite(tempStr);
				tempStr.clear();
			}

			
			//Either way, the time is presented to the user
			cout << "Maze generation time: " << genTime << endl;
			cout << "BFS sort time:        " << bfsTime << endl;
			cout << "DFS sort time:        " << dfsTime << endl;
			totTime = double((clock() - tStart))/CLOCKS_PER_SEC;
			minutes = int(totTime) / 60; //WIP
			if(minutes > 60)
				hours = int(minutes - 60) % 60;
			else
				hours = 0;
			if(hours)
			{
				totTime = totTime - (minutes * 60);
				cout << "Total time (HH:MM.SS): " << hours << ":" << minutes << "." << totTime << endl << endl;
			}
			else if(minutes)
			{
				totTime = totTime - (minutes * 60);
				cout << "Total time (MM.SS):   " <<  minutes << "." << totTime << endl << endl;
			}
			else
			{
				cout << "Total time (Seconds): " <<  totTime << endl << endl;
			}
		}
		delete theMaze; //Memory Management
		sInput.clear();
		second = true; //To check if values need to be reset or not.
	}while(!stop);
}