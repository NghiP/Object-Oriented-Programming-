#include <iostream>
#include <iomanip>
#include <cmath>
#include <cassert>


#include "ErrorContext.h"
#include "GameOfLife2_Tests.h"

using std::cout;
using std::endl;
using std::setprecision;

using Testing::ErrorContext;
using csci2312::GameOfLife;
using csci2312::Cell;
#define DESC(x) desc(x, __LINE__)  // ugly hack, but saves some time


///////// STUDENT TASK:  Fill in implementatin for Cell tests


//  Test Cell constructor and destructor
void test_cell_smoketest(ErrorContext &ec)
{
	bool pass;
	Cell *myCell;

	ec.DESC("--- Test - Cell - Smoketest ---");

	ec.DESC("Default Cell Constructor");
	pass = true;
	// Construct a Default GameOfLife - boardSize should be set to MAX_BOARD      
	myCell = new Cell;
	pass = (myCell == false);
	ec.result(pass);

	ec.DESC("Destruct Default Cell");
	// Cleans up after previous test, destruct the object        
	delete myCell;
}

//  Test Cell setters and getters
void test_cell_setget(ErrorContext &ec)
{
	bool pass;
	Cell passCell;

	ec.DESC("--- Test - Cell - Smoketest ---");

	ec.DESC("Set function");
	pass = true;
	// Construct a Default GameOfLife - boardSize should be set to MAX_BOARD
	passCell = new Cell;
	//pass = (passCell);
	ec.result(pass);
}
///////// END TASK

//  Test GameOfLife constructor and destructor
void test_game_smoketest(ErrorContext &ec) {
	bool pass;
	GameOfLife* myGame;

	ec.DESC("--- Test - GameOfLife - Smoketest ---");

	ec.DESC("Default Constructor");
	pass = true;
	// Construct a Default GameOfLife - boardSize should be set to MAX_BOARD      
	myGame = new GameOfLife;
	pass = (myGame->getBoardSize() == myGame->MAX_BOARD);
	ec.result(pass);

	ec.DESC("Destruct Defualt Test Game");
	// Cleans up after previous test, destruct the object        
	delete myGame;

	ec.DESC("Custom Constructor requesting a specific boad size");
	pass = true;
	// Construct a Custom GameOfLife - boardSize should be set to what was requested   
	myGame = new GameOfLife(50);
	pass = (myGame->getBoardSize() == 50);
	ec.result(pass);


	ec.DESC("Destruct Custom Test Game");
	// Cleans up after previous test, destruct the object        
	delete myGame;

}

// Game rules test
void test_game_rules(ErrorContext &ec) {
	bool pass;
	GameOfLife *myGame;

	// Run at least once!!
	// assert(numRuns > 0);

	ec.DESC("--- Test - Game Rule 110  ---");

	pass = true;
	// Construct a Default GameOfLife - boardSize should be set to MAX_BOARD      
	myGame = new GameOfLife;

	ec.DESC("--------- Alive cell with 2 alive neighbors  ---");
	//	pass = (myGame->executeRules(2, true) == true);
	ec.result(pass);

	ec.DESC("--------- Dead cell with 2 alive neighbors  ---");
	//	pass = (myGame->executeRules(2, false) == false);
	ec.result(pass);

	///////// STUDENT TASK:  add test for the remaining rule outcomes
	ec.DESC(" Alive Cell with less than 2 alive neighbors");
		//pass= (myGame->executeRules(<2,true)==false);
	ec.result(pass);
	
	ec.DESC("Alive Cell with more than 3 alive neighbors");
	//pass= (myGame->executeRule(>3,true)==false);
	ec.result(pass);
	///////// END TASK

	// Destruct the object at the end of test

	ec.DESC("Destruct Test Game");
	// Cleans up after previous test, destruct the object        
	delete myGame;

}



