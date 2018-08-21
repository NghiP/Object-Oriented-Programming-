using namespace std;
#include <iostream>
#include <string>
#include <algorithm>
#include "school.h"
#include <fstream>
#include <memory>


namespace csci2312
{
	People_T::People_T()
	{
		cin >> *this;
	}
	People_T::People_T(int s_num, int s_ID, string s_name)
	{
		number = s_num;
		ID = s_ID;
		name = s_name;
	}
	People_T::~People_T()
	{
	}
	//accessor and mutator
	void People_T::setnum(int p_num)
	{
		number = p_num;
	}

	int People_T::getnum() const
	{
		return number;
	}

	void People_T::setName(string p_name)
	{

		name = p_name;
	}
	string People_T::getName() const
	{
		return name;
	}
	void People_T::setID(int p_ID)
	{
		ID = p_ID;
	}
	int People_T::getID() const
	{
		return ID;
	}
	void People_T::introduction() const
	{

	}

	//instream to input into the program
	istream & operator >> (istream & ins, People_T & the_object)
	{

		{
			cout << "Please enter student number: (i.e 1)";
			ins >> the_object.number;
			cout << "Please enter the ID: (i.e 12345)";
			ins >> the_object.ID;
			//return ins;
			cout << "Please enter the name:(i.e Nghi) ";
			ins >> the_object.name;
			cout << "Add complete" << endl;
			return ins;
			
		}

	}
	//outstream operator
	ostream & operator<<(ostream & outs, const People_T & the_object)
	{
		the_object.introduction();
		outs << endl;
		return outs;
	}
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////
	ostream & operator<<(ostream & outs, const Student_T & the_object)
	{
		the_object.introduction();
		outs << endl;
		return outs;
	}
	Student_T::Student_T()
	{
	}
	Student_T::Student_T(int p_num,int p_ID, string p_name) : People_T(p_num, p_ID, p_name) {}
	void Student_T::introduction() const
	{
		cout << "My name is " << name << ". I am student number: " << number << endl;
		cout << "My student ID is " << ID << endl;
	}
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	Teacher_T::Teacher_T() {}

	Teacher_T::Teacher_T(int p_num,int p_ID, string p_name):People_T(p_num,p_ID,p_name) {}

	void Teacher_T::introduction() const
	{
		cout << "My name is " << name << ". I am a teacher number: " << number << endl;
		cout << "My teacher ID is" << ID << endl;
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////


	School_T::School_T()
	{
	}

	School_T::School_T(unsigned p_capacity)
	{
		people.reserve(p_capacity);
	}

	School_T::School_T(const School_T & p_bag)
	{
		people.reserve(p_bag.getCapacity());

		Student_T* studentPointer = NULL;
		Teacher_T* teacherPointer = NULL;

		for (unsigned i = 0; i < p_bag.getSize(); i++) {

			// To find whether Base Pointer is pointing to the Derived type of object
			// Runtime Type Identification (RTTI)
			studentPointer = dynamic_cast<Student_T*>(p_bag.people[i]);
			teacherPointer = dynamic_cast<Teacher_T*>(p_bag.people[i]);

			if (studentPointer != NULL)
			{
				people.push_back(new Student_T(*studentPointer));
			}
			else if (teacherPointer != NULL)
			{
				people.push_back(new Teacher_T(*teacherPointer));


			}
		}

	}
	//destructor
		School_T::~School_T()
		{
			for (unsigned int i = 0; i < people.size(); i++) {
				delete people[i];
			}
		}
		//capacity
		size_t School_T::getCapacity() const
		{
			return people.capacity();
		}
		//size
		size_t School_T::getSize() const
		{
			return people.size();
		}
		//add people
		void School_T::addPeople(PeoplePtr p_id)
		{
			if (people.size() < people.capacity())
			{
				people.push_back(p_id);

			}
			else
				cout << "Bag is full" << endl;
		}
		//search the school to see if found
		void School_T::searchSchool(int tag)
		{
			
			//add a new person after search
			PeoplePtr whatPeople = new People_T(tag, 0000, "nghi");
			PeoplePtr a[1] = { whatPeople };//create iterator for PeoplePrt
			it= (search(people.begin(), people.end(),a,a+1, mypredicate));
			if (it!= people.end())
			{
				cout << "People found" << endl;
				people.erase(it);
				cout << "Finish graduating/retired" << endl;
			}
			else
				cout << "People not found" << endl;


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			//Extra Credit: Smart Pointer- used this if the add function used the vector of shareed_ptr;
			/*shared_ptr <People_T> sharewhatPeople(new People_T);
			shared_ptr<People_T> b[1]{ sharewhatPeople };
			generic search algorithm
			sharedIt = (search(people.begin(), people.end(), a, a + 1, mypredicate));
			if (it != people.end())
			{
				cout << "People found" << endl;
				people.erase(it);
				cout << "Finish deleting" << endl;
			}
			else
				cout << "People not found" << endl;

			*/

		}
		//sort school
		void School_T::sortSchool()

		{
			//call the sort function
			sort(people.begin(), people.end(), compare);
			cout << "sort complete" << endl;

		}
		//return if found
		bool mypredicate(PeoplePtr i, PeoplePtr j)
		{
			return (i->getnum() == j->getnum());
		}
		//compare to sort
		bool compare(PeoplePtr p1, PeoplePtr p2)
		{
			return(p1->getnum() < p2->getnum());
		}
		//read in function
		void School_T::readin()
		{
			// Variables
			int choice;
			string input; // file to read in
			PeoplePtr tempPtr;
			PeoplePtr tempPtr1;
			int xnumber;
			int index = 0;
			int xID;
			string xName;
			//read in inventory 
			cout << "Do you want to read inventory of student or teacher?\n";
			cout << "1.Student\n";
			cout << "2.Teacher" << endl;
			cin >> choice;
			switch (choice)
			{
			case 1:
			{
				//cout << "Please enter the file to read in" << endl;
				//cin >> input;
				ifstream inputFile;
				inputFile.open("Students.txt");
				while (!inputFile.eof())
				{
					inputFile >> xnumber;
					inputFile >> xID;
					inputFile.ignore();
					getline(inputFile, xName);

					//creating a new student to stored read in value
					tempPtr = new Student_T(xnumber, xID, xName);
					//you push in to the vector
					people.push_back(tempPtr);

				}
				cout << "\nSuccess" << endl;
				inputFile.close();
				break;
			}
			case 2:
			{
				//read in file
				//cout << "Please enter the file to read in" << endl;
				//cin >> input;
				ifstream inFile;
				inFile.open("Teachers.txt");
				while (!inFile.eof())
				{

					// Have to use getline for STRING
					inFile >> xnumber;
					inFile >> xID;
					inFile.ignore();
					getline(inFile, xName);
					tempPtr1 = new Teacher_T(xnumber, xID, xName);
					people.push_back(tempPtr1);

				}
				cout << "\nSuccess" << endl;
				inFile.close();
				break;
			}
			default:
				cout << "Please select a valid choice" << endl;
			};

		}

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		void School_T::graduateS()
		{
			//graduating/delete student
			if (people.empty())
			{
				cout << "\nSorry there is no staff/student in the school." << endl;
			}
			else
			{
				// Variables
				int choice1;
				int index;

				cout << "Please enter the graduating student number" << endl;
				cin >> choice1;

				// Error check
				if (choice1 < 100 && choice1 > 0)
				{
					for (index = choice1 - 1; index < people.size() - 1; index++)
					{
						people[index] = people[index + 1];
					}
					people.pop_back();
					cout << "\nStudent #" << choice1 << " has graduated. CONGRATS!!." << endl;
				}
				else
				{
					cout << "That student number(#) is invalid." << endl;
				}
			}

		}

		void School_T::graduateSt()
		{
			//return teacher/deleting teacher
			if (people.empty())
			{
				cout << "\nSorry there is no staff/student in the school." << endl;
			}
			else
			{
				// Variables
				int choice1;
				int index;


				cout << "Please enter the retired staff number" << endl;
				cin >> choice1;

				// Error check
				if (choice1 < 100 && choice1 > 0)
				{
					for (index = choice1 - 1; index < people.size() - 1; index++)
					{
						people[index] = people[index + 1];
					}
					people.pop_back();
					cout << "\nStaff #" << choice1 << " has retired. We are sorry to see you leave!!." << endl;
				}
				else
				{
					cout << "That staff number(#) is invalid." << endl;
				}
			}
		}
		//error checking
		Bag_E::Bag_E(string p_error_message)
		{
			errorMessage = p_error_message;
		};
		//exception handling
		void Bag_E::handleError()
		{
			cout << errorMessage << endl;
			//  
		};
		ostream & operator<<(ostream & outs, const School_T & the_object)
		{
			for (unsigned i = 0; i < the_object.people.size(); i++) {
				outs << *(the_object.people[i]);
			};
			return outs;
		}


	
}




