#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

#include "school.h"

using namespace csci2312;


// ======================
//     main function
// ======================
int main()
{
	//Extra Credit
	vector<Computer*> computers;

	std::string comp;

	std::cout << "What type of computer?? ";
	std::getline(std::cin, comp); computers.push_back(ComputerFactory::NewComputer(comp));
	Laptop* lap = dynamic_cast<Laptop*>(computers[0]); if (lap != NULL)
		std::cout << computers[0]->getBrand(); // "Laptop added \n";

	School_T mySchool(100); // Instantiates a Bag_T
	cout << "Number of staff/student: " << mySchool.getSize() << endl;
	cout << "School Capacity : " << mySchool.getCapacity() << endl;

	string people_name;
	int choice = -1;

	// Main Menu
	while (choice != 0)
	{
		cout << endl;

		cout << "MAIN MENU" << endl;
		cout << "0) Quit" << endl;
		cout << "1) Add Student" << endl;
		cout << "2) Add Teacher" << endl;
		cout << "3) School Inv" << endl;
		cout << "4) Search" << endl;
		cout << "5) Sort  " << endl;
		cout << "6) Graduating student/Graduate entire student" << endl;
		cout << "7) Retire Staff/Retire all staff" << endl;
		cout << "8)Read in student/staff to school" << endl;
		cin >> choice;

		switch (choice) {
		case 0:
			return 0;
		case 1:
			//exception handling
			try {
				mySchool.addPeople(new Student_T); // Polymorphism: addPet is defined to add generic Pat_T, but passes in Cat_T
			}
			catch (Bag_E e)
			{
				e.handleError();
			}
			break;
		case 2:
			try {   // Polymorphism: addPet is defined to add generic Pat_T, but passes in Dog_T
				mySchool.addPeople(new Teacher_T);
			}
			catch (Bag_E e)
			{
				e.handleError();
			}
				
			break;
		case 3:
			cout << mySchool;
			// Prints content of Bag
			break;
		case 4:
			int s;
			//search the student by number
			cout << "Enter the student number to search and graduate/retiring" << endl;
			cin>> s;
			mySchool.searchSchool(s);
			break;
		case 5:
			//sort the student by ID
			mySchool.sortSchool();
			break;
		case 6:
			//delete student
			int ans;
			cout << mySchool;
			cout << "Would you like to graduate all student?\n";
			cout << "1) yes\n";
			cout << "2) no\n";
			cout << "3)exit\n";
			cin >> ans;
			switch (ans)
			{
			case 1:
				//graduating all student
				mySchool.closure<Student_T>();
				cout << "Finish graduating all student! Hope they have a bright future ahead." << endl;
				break;
			case 2:
				//graduating 1 student
				cout << "Graduating one student" << endl;
				mySchool.graduateS();
				break;
			case 3:
				return 0;
			default:
				cout << "enter a valid choice" << endl;
			}
		
			break;
		case 7:
			//delete teacher
			int anst;
			cout << mySchool;
			cout << "Would you like to retired all teacher?\n";
			cout << "1) yes\n";
			cout << "2) no\n";
			cout << "3)exit\n";
			cin >> anst;
			switch (anst)
			{
			case 1:
			//deleting entire teacher class
				mySchool.closure<Teacher_T>();
				cout << "Retire all teacher! We are sad to see you go" << endl;
				break;
			case 2:
				//deleting one person
				cout << "Retiring one teacher" << endl;
				mySchool.graduateSt();
				break;
			case 3:
				return 0;
			default:
				cout << "enter a valid choice" << endl;
			}

			break;
			
		case 8:
			//read in file
			mySchool.readin();
			break;			
		default:
			cout << " Please select choice 0-8" << endl;
		};
	}

	system("pause");

	return 0;
}

