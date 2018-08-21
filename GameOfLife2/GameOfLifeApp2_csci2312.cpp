// *********************************************************************
//  This program demostrates the Game Of Life 
//	Nghi Phan
//	CSCI 2312
//	Due Date: 3/12/2017
//	Status: Complete and Compile to the criteria
// *********************************************************************
//main

#include "GameOfLife2_csci2312.h" //header file

using std::cout;
using std::endl;
using std::cin;
using namespace csci2312;

int main()
{
	std::cout << "\t\tJOHN CONWAY'S GAME OF LIFE\n"
		<< "\nRULES 1:\n"
		<< "1. Alive cell with < 2 alive neighbours dies (under-population)\n"
		<< "2. Alive cell with 2 or 3 alive neighbours lives\n"
		<< "3. Alive cell with > 3 alive neighbours dies (over-population)\n"
		<< "4. Dead cell with 3 live neighbours becomes a live cell (reproduction)\n";

	int numberOfGenerations; // to determine # of game iterations
	char userInput = 'y';
		
		size_t userBoardSize=0;
		while (userBoardSize < 1) //the board must be greater than 0
		{
			cout << "\nEnter the board size: ";
			cin >> userBoardSize;
		}
		GameOfLife* myGame;
		try     //error catching
		{

			myGame = new GameOfLife(userBoardSize);
		}
		catch (std::bad_alloc) //catch the program if fail to allocate memory for game
		{
			cout << "Failed to allocate memory for a new game" << endl;

			cin.get();
			return(1);
		};

		std::cout << "How many generations would you like to run?" << endl;
		::cout << "A number- for the number of generation" << endl;
		::cout << "0 - step by step through each generation" << endl;
		cin >> numberOfGenerations;
		cout << "The numeber of genneration input is " << numberOfGenerations << endl;

		if (numberOfGenerations == 0)
			myGame->run(userBoardSize); //Step-by-step run function with user defined board size
		else if (numberOfGenerations> 0)
			myGame->run(numberOfGenerations, userBoardSize); //run function with user defined generations and board size
		else //(numberOfIterations < 0)
			std::cout << "Number must be greater or equal to 0.\n";
		cout << "Exit" << endl;

		delete myGame; // call the GameOfLife destructor
		//system("PAUSE");
	return 0;
}

