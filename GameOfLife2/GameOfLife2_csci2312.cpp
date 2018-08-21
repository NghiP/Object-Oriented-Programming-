#include "GameOfLife2_csci2312.h" //header file
#include "..\..\..\Desktop\GameOfLife2\GameOfLife2_csci2312.h"

using std::cout;
using std::endl;
namespace csci2312
{
Cell::Cell()			//setting the cell to dead
{
		face = dead;
}

Cell::Cell(bool cellState)
{
		state = cellState; //initializes cell state  
}
Cell::~Cell()	//cell destructor, doesn't have anything in it
{
}
bool Cell::getState() const	//return state
{
		return state;
}
void Cell::setState(bool newState)
{
		state = newState;	//set state to new state
}
char Cell::getFace() const	//get the cell state dead or alive
{
		if (getState() == 1) //face determined by current cell state
		{
			return alive;	//return alive if 1
		}
		else
		{
			return dead;		//return deao if 0
		}
}
GameOfLife::GameOfLife(size_t myBoardSize)
{
		boardSize = myBoardSize; //Initialize boardSize
		currentLife = new CellPtr[boardSize];	//set current life to cellPtr
		for (size_t i = 0; i < boardSize; i++)
		{
			currentLife[i] = new Cell[boardSize];
		}
		for (size_t row = 0; row < boardSize; row++)
		{
			for (size_t col = 0; col < boardSize; col++) { currentLife[row][col].setState(0); }
		}
		fileInput = new char*[boardSize];	//set the read in file to char
		for (size_t i = 0; i < boardSize; i++)
		{
			fileInput[i] = new char[boardSize];
		}
		nextLife = new CellPtr[boardSize];    //set next life to cellPtr
		for (size_t i = 0; i < boardSize; i++)
		{
			nextLife[i] = new Cell[boardSize];
		}
		for (size_t row = 0; row < boardSize; row++)
		{
			for (size_t col = 0; col < boardSize; col++)
			{
				nextLife[row][col].setState(0);
			}
		}
}//for userinput size
GameOfLife::GameOfLife(const GameOfLife & gameToCopy)	//copy constructor
{
		boardSize = gameToCopy.boardSize;
		if (gameToCopy.currentLife)
		{
			currentLife = new CellPtr[gameToCopy.boardSize*gameToCopy.boardSize];	//create a new cellptr to store the copy
			memcpy(currentLife, gameToCopy.currentLife, boardSize*boardSize);	//copy everything over: code from cpluscplus.com
		}
		else
		{
			currentLife = nullptr;	//set current life to nullptr if there is no data
		}
}
GameOfLife::~GameOfLife() //destructor
{
		for (size_t i = 0; i < boardSize; i++)
		{
			delete[] currentLife[i];	//delete all the new ptr 
			delete[] nextLife[i];
			delete[] fileInput[i];
		}
		delete[]currentLife;
		delete[]nextLife;
		delete[]fileInput;
		cout << "\n All pointer are deleted\n";
};
size_t GameOfLife::getBoardSize() const
{
		return boardSize; //returns current boardSize
}
void GameOfLife::seedBoard(string fileName, size_t sizeBoard)throw (FileIOException)
{
		string dataFile = fileName;
		std::ifstream readData(fileName);
		fileName = "inputFile.txt";
		GameOfLife* game = new GameOfLife(sizeBoard); //allocate memory for a new game board
		if (readData.is_open()) // check if can  file opening
		{
			while (!readData.eof()) //Continue reading 
			{
				readData >> *game; //read in the data and derefference it
								   //Uses file characters and sets currentLife board to 1 or 0 based on alive or dead characters
				for (size_t row = 0; row < game->getBoardSize(); row++)
				{
					for (size_t col = 0; col < game->getBoardSize(); col++)
					{
						if (game->fileInput[row][col] == 'o')
						{
							currentLife[row][col].setState(1);
						}
						else
						{
							currentLife[row][col].setState(0);
						}
					}
				}
			}
		}
		else //cant open file
		{
			cout << "Error opening file.\n";
			std::cin.get();
		}
		readData.close(); //close the file
}
void GameOfLife::seedBoard(size_t seeds)	//seed the board
{
		size_t row, col;
		for (size_t i = 1; i <= seeds; i++) //Creates a user defined number of random seeds
		{
			row = 1 + rand() % boardSize - 1; //Creates a random row and col randomly
			col = 1 + rand() % boardSize - 1;
			currentLife[row][col].setState(true);
		}
}
void GameOfLife::seedBoard()
{
		size_t sizeB = 0;
		do
		{
			cout << " Enter the size board: " << endl;
			std::cin >> sizeB; //user input the amount of cell
		} while (sizeB < 0 || sizeB >= 30); //check if the size enter is between 0 and 30

		if (sizeB != 0) //If not 0
		{
			GameOfLife* game = new GameOfLife(sizeB); //create new memory for user input board
			char cont;
			cout << "Input " << sizeB*sizeB << " characters of either '-' or 'o'" << endl;
			std::cin >> *game;
			std::cout << "continue the game (y/n)" << endl;
			std::cin >> cont;
			if ((cont == 'y') || (cont == 'Y'))	//continue to game after making the board
			{
				for (size_t row = 0; row < game->getBoardSize(); row++)		//go into the game and set the state enter by user
				{
					for (size_t col = 0; col < game->getBoardSize(); col++)
					{
						if (game->fileInput[row][col] == 'o')
						{
							currentLife[row][col].setState(1);
						}
						else
						{
							currentLife[row][col].setState(0);
						}
					}
				}
			}
			else
				return;
		}
}
void GameOfLife::run(size_t sizeBoard)	//running the program step by step
{
	GameOfLife game = GameOfLife(sizeBoard);
	char choice = '0';
	size_t numOfSeeds = 0;
	int ruleSet = 0;
	//bool invalidEntry = false;
	string fileName = "inputFile.txt"; //fileName initialized to inputFile.txt
	std::ifstream testFile;
	//Main menu for user
	std::cout << "\nMAIN MENU: " << endl;
	::cout << " 1. Generate random file" << endl;
	::cout << " 2. Input a text file" << endl;
	::cout << "3. Make own board" << endl;
	::cout << "4. Exit" << endl;
	std::cin >> choice;

	switch (choice)
	{
	case '1':	//generate a random file
		cout << "Enter the number of seeds to generate: "; //User inputs a number of seeds
		std::cin >> numOfSeeds;
		{
			game.seedBoard(numOfSeeds);
			//invalidEntry = false; //user input valid
		}
		break;
	case '2': //read in from a text file
		cout << "Read in from inputFile.txt:\n ";
		fileName == "inputFile.txt";
		testFile.open(fileName);
		if (testFile.is_open())
		{
			game.seedBoard(fileName, game.getBoardSize());
			//invalidEntry = false; //valid entry input by user
		}
		else
		{
			cout << "Error opening file.\n";
			//invalidEntry = true; //invalid entry by user or bad file
		}
		break;
	case '3': //user input board from keyboard
		game.seedBoard();
		break;
	case '4': //exit program
		std::cout << "Exititing the Game.\n";
		break;
	default: //1-4 was not entered
		std::cout << "\nPlease enter choice 1-4\n";
		//invalidEntry = true;
		break;
	}
	// user input 1-4 continue
	if ((choice == '1' || choice == '2' || choice == '3'))
	{
		{
			cout << game << endl; //display current board

			while (continueGame() == true) //loop while user wants to continue
			{
				game.calculateNextGen(game.currentLife, game.nextLife); //calculates next generation

				std::cout << game << std::endl; //display game

				for (size_t r = 0; r < boardSize; r++)
				{
					for (size_t c = 0; c < boardSize; c++)
					{
						game.currentLife[r][c].setState(game.nextLife[r][c].getState()); //Sets next generation to current generation
					}
				}
			}
		}
	}
	else
		cout << "\nError.\n"; //used if invalid random seed amount was entered
}

bool GameOfLife::executeRule110(unsigned int countAlive, bool currentState)	//excuting Rule 1
{
		if (currentState == true && countAlive < 2)		//if less than 2, dead
		{
			return false;
		}
		else if (currentState == true && (countAlive == 2 || countAlive == 3))	//if between 2 and 3, alive
		{
			return true;
		}
		else if (currentState == true && countAlive > 3)		//if greater than 3, dead
		{
			return false;
		}
		else if (currentState == false && countAlive == 3)		//if surround by 3 alive cell, alive
		{
			return true;
		}
		else
		{
			return false;
		}
}
void GameOfLife::calculateNextGen(CellPtr* current, CellPtr* next)	//calculate next generation for first rule 
{
		Cell temp;
		for (size_t row = 1; row < boardSize - 1; row++)	//creating a halo for the side cell
		{
			for (size_t col = 1; col < boardSize - 1; col++)
			{
				int liveCount = 0;
				if (current[row - 1][col - 1].getFace() == temp.alive)
				{
					liveCount++;
				}
				if (current[row - 1][col].getFace() == temp.alive)
				{
					liveCount++;
				}
				if (current[row - 1][col + 1].getFace() == temp.alive)
				{
					liveCount++;
				}
				if (current[row][col - 1].getFace() == temp.alive)
				{
					liveCount++;
				}
				if (current[row][col + 1].getFace() == temp.alive)
				{
					liveCount++;
				}
				if (current[row + 1][col - 1].getFace() == temp.alive)
				{
					liveCount++;
				}
				if (current[row + 1][col + 1].getFace() == temp.alive)
				{
					liveCount++;
				}
				if (current[row + 1][col].getFace() == temp.alive)
				{
					liveCount++;
				}
				int num = liveCount;
				bool nextState = executeRule110(num, currentLife[row][col].getState());	//execute rule 1
				next[row][col].setState(nextState);	//set it as the state
			}
		}
}

void GameOfLife::run(unsigned int numberOfGenerations, size_t sizeBoard)    //user choose the number of generation
{
	GameOfLife game = GameOfLife(sizeBoard);
	char choice = '4';
	size_t numOfSeeds = 0;
	int ruleSet = 0;
	string fileName = "inputFile.txt"; //fileName initialized to inputFile.txt
	std::ifstream testFile;
	//Main menu for user
	std::cout << "\nMAIN MENU: " << endl;
	::cout << " 1. Generate random file" << endl;
	::cout << " 2. Read in from a text file" << endl;
	::cout << "3. Make own board" << endl;
	::cout << "4. Exit" << endl;
	std::cin >> choice;

	switch (choice)
	{
	case '1':	//generate a random file
		cout << "Enter the number of seeds to generate: "; //User inputs a number of seeds
		std::cin >> numOfSeeds;
		{
			game.seedBoard(numOfSeeds);
		}
		break;
	case '2':	//read in a text file
		cout << "Read in from inputFile.txt: \n ";
		fileName == "inputFile.txt";
		testFile.open(fileName);
		if (testFile.is_open())
		{
			game.seedBoard(fileName, game.getBoardSize());
		}
		else
		{
			cout << "Error opening file.\n";
		}
		break;
	case '3': //user input board from keyboard
		game.seedBoard();
		break;
	case '4': //exit program
		std::cout << "Thanks for playing.\n";
		break;
	default: //1-4 was not entered
		std::cout << "\nPlease enter choice 1-4\n";
		break;
	}
	// Only perform game of life calculations if a valid entry was input
	if ((choice == '1' || choice == '2' || choice == '3'))//&& invalidEntry==false
	{
		{
			std::cout << game << std::endl; //display game
			while (numberOfGenerations != 0) //User enters 0 to exit loop
			{
				for (size_t i = 0; i < numberOfGenerations; i++) //game loops for user input number of iterations
				{
					game.calculateNextGen(game.currentLife, game.nextLife); //calculate next generation with standard rule set
					std::cout << game << std::endl; //display game
					for (size_t r = 0; r < boardSize; r++)
					{
						for (size_t c = 0; c < boardSize; c++)
						{
							game.currentLife[r][c].setState(game.nextLife[r][c].getState()); //Current state is the previous next state
						}
					}
				}
				int numTemp = 0;
				cout << "More generations?\n"
					<< "0 - To exit\n"
					<< "Enter number of Generations- To continue\n";
				std::cin >> numTemp; //continue for more generations or exit loop if user enters 0
				if (numTemp >= 0)
					numberOfGenerations = numTemp;
				else
				{
					cout << "\nInvalid input.\n"; // if user enters number less than 0, invalid input displayed and loop is exited
					numberOfGenerations = 0;
				}
			}
		}
	}
}
ostream& operator << (ostream& out, const Cell& cell)	//overloading the operator to output the cell state
{
		out << (cell.getState() ? cell.alive : cell.dead);
		return out;
}
ostream& operator << (ostream& output, const GameOfLife& board) //overloadind the operator to output the board
{
		size_t row, col;
		for (row = 0; row < board.boardSize; row++) {
			for (col = 0; col < board.boardSize; col++)
			{
				output << board.currentLife[row][col].getFace(); //display boards current face at each position
			}           output << std::endl;
		}
		output << std::endl;
		return output;
}
	// Ifstream to input a board 
istream & operator >> (istream & input, GameOfLife & board)
{
		for (size_t row = 0; row < board.getBoardSize(); row++)
		{
			for (size_t col = 0; col < board.getBoardSize(); col++)
			{               //input goes to a dynamic char fileInput member
				input >> board.fileInput[row][col];
			}
		}       return input;
	}
}

bool continueGame()	 //ask the user at the end if they want to continue or exit the program
{
	char cont;
	std::cout << "Continue? (y/n)\n";
	std::cin >> cont;

	if (cont == 'y' || cont == 'Y')
		return true;
	else
		return false;
}
