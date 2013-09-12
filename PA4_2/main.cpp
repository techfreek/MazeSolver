#include"mazeFuncs.h"
#include<time.h>
#include<iostream>
#include<string>

int main(int argc, char* argv[])
{
	srand(time(NULL));
	int arr_size = 5,
		loops = 0,
		newLoops = 0,
		cap = 1000;
	char* tempchar =  new char();
	char boolean = '\0';
	string fileName,
		tempStr;
	if(argv[1] != NULL)
		fileName = argv[1];
	
	maze* theMaze = NULL;
	vector<mazeNode*>* mazeVector;
	vector<mazeNode*>* mazeVectorOLD;

	double genTime = 0,
		bfsTime = 0,
		dfsTime = 0,
		totTime = 0;

	int minutes = 0,
		hours = 0,
		timer = 0,
		oldTimer = 0;

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

cout << "Welcome to Maze Solving! "<< endl; //some introduction text because I was bored
cout << " Created by: Alex Bahm" << endl;
cout << " Cpts 223 WSU" << endl;
cout << " April 2013" << endl << endl;
//cout << "This code has been tested to work, however through multiple iterations of " << endl;
//cout << "running, it has been known to crash. This only happens rarely. In addition," << endl;
//cout << "occasionally maze generation will fail, simply try again and it should work" << endl << "fine. " << endl;
                       

cout << endl;
	do{
		//tStart = NULL; //resets the clock
		 //I use a clock purely for curiosities sake
		if(second)
		{
			second = false;
			loops = 0;
			file = false;
			stop = false;
			clock_t tStart = NULL,
			genStart = NULL,
			dfsStart = NULL,
			bfsStart = NULL,
			oldStart = NULL,
			oldDone = NULL;
			theMaze = NULL;
			mazeVector = NULL;
		}
		if(fileName.empty())
		{
			cout << "Do you want to import a maze? (T/F): ";
			cin >> boolean;
		}
		//boolean = 't'; //for debugging
		if(tolower(boolean) == 'e')
		{
			exit(1);
		}
		else if(tolower(boolean) == 'o')
		{
			old = true;
		}
		else if(tolower(boolean) == 't' || !fileName.empty())
		{
			file = true;
			if(fileName.empty())
			{
				cout << "What is the file name? ";
				cin >> fileName;
			}
			//fileName = "maze9.txt"; //also for debugging
			genStart = clock();
			tStart = clock();
			mazeVector = readFile(fileName);
			cout << "Read and maze generation time: " << double((clock() - genStart))/CLOCKS_PER_SEC << endl;
			if(mazeVector == NULL)
				theMaze = NULL;
			else
			{
				theMaze = new maze(mazeVector); //reads file, generates a maze, returns a vector, then makes the maze class
				theMaze->printMaze(); //prints maze
			}
		}
		if(tolower(boolean) == 'f' || tolower(boolean) == 'o')
		{
			do{
				loops = 0;
				if(arr_size < 2) // so we dont get an incredibly tiny maze, may cause some problem
					cout << "Please enter a larger number. " << endl;
				else if(arr_size > cap) //I have trouble generating above 20 to begin with, so hene a cap
					cout << "For the sake of your computer, please enter a smaller number. " << endl;
				cout << "How big of a maze would you like made? ";
				cin >> arr_size;
			}while(arr_size < 2 || arr_size > cap);
			cout << "Maze size: " << arr_size << " x " << arr_size << "; Nodes: " << arr_size * arr_size << endl;
			genStart = clock();
			tStart = clock();
			cout << "Processing Time: " << endl;
			if(!old)
				cout << "\r" << (clock() - genStart)/CLOCKS_PER_SEC << flush;;
			do{
				if(!old)
					mazeVector = mazeGen(arr_size, genStart);
				else
					mazeVector = mazeGenOLD(arr_size);
				loops++; //counts how many loops so it doesn't go on forever trying to achieve a maze
				//cout << "."; //so users know the program has not entered an infinite loop
			}while(mazeVector == NULL && loops < (3 * arr_size));

			cout << endl;
			genTime = double(clock() - genStart)/CLOCKS_PER_SEC;

			if(loops >= (3 * arr_size))
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
			
			/*cout << "Testing old maze generation algorithm";
			oldStart = clock();
			newLoops = loops;
			loops = 0;
			do{
				mazeVectorOLD = mazeGenOLD(arr_size);
				loops++; //counts how many loops so it doesn't go on forever trying to achieve a maze
				cout << "."; //so users know the program has not entered an infinite loop
			}while(mazeVectorOLD == NULL && loops < (5 * newLoops));

			if(loops >= (5 * newLoops))
				cout << " - FAILED!!!" << endl;
			else
				cout << endl;

			oldDone = clock() - oldStart;
			cout << "Old Algorithm Time: " << double(oldDone)/CLOCKS_PER_SEC << endl;
			cout << endl << "Difference: " << double(oldDone - genTime)/CLOCKS_PER_SEC << endl;*/

		}
		else
			cout << "Please chose T/F next time." << endl;
		if(theMaze != NULL)
		{
			bfsStart = clock();
			theMaze->bfs(); //does the bfs algorithm on from file or random maze
			bfsTime = double((clock() - bfsStart))/CLOCKS_PER_SEC;
			cout << endl << endl;
			dfsStart = clock();
			theMaze->dfs(); //does the dfs algorithm
			dfsTime = double((clock() - dfsStart))/CLOCKS_PER_SEC;			

			if(arr_size > 40)
			{
				
				tempStr.append("Maze Size: ");
				itoa(arr_size, tempchar, 10);

				tempStr.append(string(tempchar));
				tempStr.append(" x ");
				tempStr.append(string(tempchar));
				tempStr.append("; Nodes: ");
				itoa((arr_size * arr_size), tempchar, 10);
				tempStr.append(string(tempchar));
				theMaze->fileWrite(tempStr);
				tempStr.clear();

				tempStr.append("Maze Generation Time: ");
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

			

			cout << "Maze generation time: " << genTime << endl;
			cout << "BFS sort time:        " << bfsTime << endl;
			cout << "DFS sort time:        " << dfsTime << endl;
			totTime = double((clock() - tStart))/CLOCKS_PER_SEC;
			minutes = int(totTime) / 60;
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
		delete theMaze;
		second = true;
	}while(!stop);
}