#ifndef SCHOOL_H
#define SCHOOL_H

#include <iostream>
#include <string>
#include <vector>

namespace csci2312
{

	class People_T
	{
	public:

		// Default Constructor
		People_T();


		// Constructor sets name
		People_T(int num, int s_ID, string s_name);

		// Destructor
		~People_T();

		// Accessors and Mutators
		void setnum(int p_num);
		int getnum()const;
		void setName(string p_name);
		string getName() const;
		void setID(int p_ID);
		int getID()const;

		// People introduces himself. Only concrete derived classes implement it
		void virtual introduction() const;

		//Overloads the >> operator for input values of type People_T.  Optional		
		friend istream& operator >> (istream& ins, People_T& the_object);
		//Precondition: If ins is a file input stream, then ins has already been
		//connected to a file.

		//Overloads the << operator for output values of type People_T.
		friend ostream& operator <<(ostream& outs, const People_T& the_object);
		//Precondition: If outs is a file output stream, then outs has already been
		//connected to a file.

	protected:
		string name;
		int ID;
		int number;

	};

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// Use 'typedef' to define a new type called PeoplePtr which is a pointer to People_T
	typedef People_T* PeoplePtr;

	class Student_T : public People_T {
	public:

		// Default constructor
		Student_T();

		// Constructor sets name/ID
		Student_T(int s_num,int s_ID, string p_name);

		// Student introduces himself: "My name is <name>.  I am a student."
		void virtual introduction() const override;

		//Overloads the << operator for output values of type student_T.
		friend ostream& operator <<(ostream& outs, const Student_T& the_object);
		//Precondition: If outs is a file output stream, then outs has already been
		//connected to a file.
	};


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	class Teacher_T : public People_T {
	public:

		// Default constructor
		Teacher_T();

		// Constructor sets name
		Teacher_T(int p_num,int p_ID, string p_name);

		// Teacher introduces himself: "My name is <name>.  I am a teacher."
		void virtual introduction() const override;
	private:
	};



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	class School_T {
	public:

		School_T();
		// Contructor to sets size of Bag
		School_T(unsigned p_capacity);

		// Copy bag
		School_T(const School_T& p_bag);

		// Destructor
		~School_T();

		size_t getCapacity() const;
		size_t getSize() const;

		// Adds People to Bag
		void addPeople(PeoplePtr p_id);
		// Search content of school
		void searchSchool(int tag);

	//	typedef std::shared_ptr<People_T>PeoplePtr;
		//sort the content of the school
		void sortSchool();
		void readin();
		//graduating student/staff
		void graduateS();
		void graduateSt();
		//template to close school
		template<typename People_T>void closure();

		friend ostream& operator <<(ostream& outs, const School_T& the_object);
		//Overloads the << operator for output content of type School_T.
		//Precondition: If outs is a file output stream, then outs has already been
		//connected to a file.
	private:
		vector<PeoplePtr> people;
		//iterator for search
		vector<PeoplePtr>::iterator it;
	};
	//compare for sort
	bool compare(PeoplePtr p1, PeoplePtr p2);
	//my predicate for search
	bool mypredicate(PeoplePtr i, PeoplePtr j);
	//class for error handling
	class Bag_E 
	{
	private:
		string errorMessage;
	public:
		//  Constructor set a message
		Bag_E(string);
		void handleError();
	};
	//declaration of the template
	template<typename People_T>
	inline void School_T::closure()
		{
			People_T *peoplePointer = nullptr;
			for (unsigned count = 0; count < people.size(); count++)
			{
				peoplePointer = dynamic_cast<People_T*>(people[count]);
				if (peoplePointer != nullptr)
				{
					delete people[count];
					people.erase(people.begin() + count);
					count--;
				}

			}
		};
	
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Extra Credit
class Computer
{
public:
	Computer(std::string b) : brand(b) {}; virtual void Run() = 0; virtual void Stop() = 0; virtual std::string getBrand() = 0;
	virtual ~Computer() {}; 
	protected: std::string brand;
}; class Laptop : public Computer {
public:
	Laptop(std::string b) : Computer(b) {}; void Run() override { mHibernating = false; }; void Stop() override { mHibernating = true; }; virtual ~Laptop() {}; 
	std::string getBrand() override { return ("Laptop: " + brand); }
private:
	bool mHibernating; // if the machine is hibernating
}; 
class Desktop : public Computer
{
public:
	Desktop(std::string b) : Computer(b) {}; void Run() override { mOn = true; }; void Stop() override { mOn = false; };
	virtual ~Desktop() {}; std::string getBrand() override { return ("Deskptop: " + brand); }
private:
	bool mOn; // if the machine has been turned on
};
// 
class ComputerFactory 
{
public:
	static Computer *NewComputer(std::string &description)
	{
		if (description == "laptop") return new Laptop("Asus"); if (description == "desktop") return new Desktop("MAC"); return NULL;
	}
};



#endif // SCHOOL_H

