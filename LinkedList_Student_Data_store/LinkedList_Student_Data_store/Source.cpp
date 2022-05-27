
/*
Team 1
Assignment 3
Student Data Store | Student Data Store Implmentation Using Signle Linked List
*/

#include <iostream>
#include <string>
#include<string.h>
#include <algorithm>
using namespace std;

/*
-Class Student
-Contains Student data 
-Contains a copy constructor used to copy an instant of the class into other objects
*/
class Student {
public:
	string fullName;
	double GPA;
	int level;
	Student();
	Student(string fullName, double GPA, int level);
	Student(const Student& old_obj);
};
/*
-No parameter constructor used to intialize student data
*/
Student::Student() {
	fullName = "";
	GPA = 0;
	level = 0;
}
/*
-Overloaded parameter constructor used to intialize student data
*/
Student::Student(string fullName, double GPA, int level) {
	this->fullName = fullName;
	this->GPA = GPA;
	this->level = level;
};
/*
-Copy constructor used to copy instances of an object
*/
Student::Student(const Student& old_obj) {
	fullName = old_obj.fullName;
	GPA = old_obj.GPA;
	level = old_obj.level;
};

/*
-Template class Node used to store Linked List data
-Contains the data field which has a dynamic data type depends on the need of the user
-Contains next pointer which points to the next node in the linked list
*/
template <class Type>
class Node {
public:
	Type data;
	Node* next;
	Node(Type val);
};
/*
-Node constructor used to intialize Node data
*/
template <class Type>
Node<Type>::Node(Type val) {
	data = val;
	next = NULL;
}
/*
-Class Linked_List which is a single list used to store data in the memory dynamically
-Homogenous, Dynamic, Linear data structure
-Contains head pointer which is a pointer of the first element in the list
-Contains an intger size which indicates the size of the list
*/
template <class Type>
class Linked_List {
	Node<Type>* head;
	int size;
public:
	Linked_List();
	~Linked_List();
	void insertFirst(Type val);
	void insertLast(Type val);
	void insertAfter(Type val, int pos);
	Type removeFirst();
	Type removeLast();
	void removeStudent(string fullName);
	bool isValidForOperation(string fullName);
	void updateStudentInfo(string fullName, double GPA, int level);
	Student studentSearch(string fullName);
	int get_size() { return size; }
};
/*
-Linked_List constructor used to intialize the head pointer to null and set the size to 0
*/
template <class Type>
Linked_List<Type>::Linked_List() {
	head = NULL;
	size = 0;
}
/*
-Linked_list destructor used to remove nodes from the memory as it was implemented dynamically
so it has to be removed manually
*/
template<class Type>
Linked_List<Type> :: ~Linked_List() {
	while (head != NULL) {
		Type temp = removeFirst();
	}
}
/*
-InsertFirst function used to insert nodes in the list as the first node
-Takes a value of the user that would be later assigned to the node depending on the type of the list
-if the list is empty the node is implemented as the first node
-if the list is not empty the head pointer is moved and the newnode must point at the node that was last the first node
*/
template<class Type>
void Linked_List<Type>::insertFirst(Type val) {
	size++;
	Node<Type>* newNode = new Node<Type>(val);
	if (head == NULL) {
		head = newNode;
	}
	else {
		newNode->next = head;
		head = newNode;
	}
}
/*
-insertLast function used to insert nodes in the list as the last node
-if the list is empty the node is implemented as the first node
-if the list is not empty a pointer is used to point at the last element and then its next pointer is connected to the newNode

*/
template <class Type>
void Linked_List<Type> ::insertLast(Type val) {
	size++;
	Node<Type>* newNode = new Node<Type>(val);
	if (head == NULL) {
		head = newNode;
	}
	else {
		Node<Type>* ptr = head;
		while (ptr->next != NULL) {
			ptr = ptr->next;
		}
		ptr->next = newNode;
	}

}
/*
insertAfter function used to implement nodes in the list after a certain node
-Takes a value of the user that would be later assigned to the node depending on the type of the list and the poistion
of the node that the newNode would be implemented after
-First we intialize a pointer that searches for the node that we would implement the newNode after
-if that node was not found an error message is printed to the user and the function terminates
-if it was found newNode's next pointer takes the value of the next pointer of that node and that node next pointer is then
assigned to the new one
*/
template<class Type>
void Linked_List<Type> ::insertAfter(Type val, int pos) {
	size++;
	Node<Type>* ptr = head;
	int i = 0;
	while (ptr != NULL && i < pos) {
		ptr = ptr->next;
		i++;
	}
	if (ptr == NULL || i != pos) {
		cout << "Position not found\n";
		return;
	}
	Node<Type>* newNode = new Node<Type>(val);
	newNode->next = ptr->next;
	ptr->next = newNode;
}
/*
-removeFirst function is used to remove the first node in the list and returns that node to the user
-if the node is empty an error message is printed to the user and the function terminates
-if not a pointer is assigned to that node, the head pointer is moved to the next node and that node is deleted using that pointer
*/
template <class Type>
Type Linked_List<Type>::removeFirst() {
	size--;
	if (head == NULL) {
		cout << "List is empty\n";
		system("pause");
		exit(1);
	}
	else {
		Type val = head->data;
		if (head->next == NULL) {
			delete(head);
			head = NULL;
		}
		else {
			Node<Type>* ptr = head;
			head = ptr->next;
			delete(ptr);
		}
		return val;
	}
}
/*
-removeLast function is used to remove the last node in the list
-if the node is empty an error message is printed to the user and the function terminates
-if not a pointer is intialized to point at the node before last
-then a pointer is assigned to the last node and is then deleted using that pointer
-the node before the last is set up as the last node in the list
*/
template <class Type>
Type Linked_List<Type>::removeLast() {
	size--;
	if (head == NULL) {
		cout << "List is empty\n";
		system("pause");
		exit(1);
	}
	else {
		Type val;
		if (head->next == NULL) {
			val = head->data;
			delete(head);
			head = NULL;
		}
		else {
			Node<Type>* ptr = head;
			while (ptr->next->next != NULL) {
				ptr = ptr->next;
			}
			data = ptr->next->data;
			delete(ptr->next);
			delete(ptr);
		}

		return val;
	}
}
/*
-isValidForOperation function is used to return a boolean value if the student exist in the linked list
-Takes a string input from the user as the fullName and that string is used to search the list to check if the student exist or not
-A pointer is assigned to the head of the list and enters a while loop to stop at the student node if exist
-if it doesn't exist in the list a false value is returned to the user
-if it does exist in the list a true value is returned to the user
*/
template <class Type>
bool Linked_List<Type> ::isValidForOperation(string fullName) {
	Node<Student>* ptr = head;
	while (ptr != NULL && ptr->data.fullName != fullName)
	{
		ptr = ptr->next;
	}
	if (ptr == NULL)
	{
		return false;
	}
	return true;
}
/*
-removeStudent function is used to search the list for the student node using student fullName to be then deleted
-Takes a string input from the user as the fullName
-if the list is empty an error message is printed to the user and the function is terminated
-if the student exist in the firstNode that node is to be delted using removeFirst() function
-if not a pointer is intialzed to the head of the list to search for that student node using a while loop to stop right before 
the node that we wish to delete
if it is not found an error message is printed to the user and the function is terminated
-if it is found it is deleted using a pointer
*/
template <class Type>
void Linked_List<Type>::removeStudent(string fullName) {
	if (head == NULL) {
		cout << "Linked List is empty\n";
		return;
	}
	else if (head->data.fullName == fullName) {
		removeFirst();
		return;
	}
	Node<Type>* ptr = head;
	while (ptr->next != NULL && ptr->next->data.fullName != fullName) {
		ptr = ptr->next;
	}
	if (ptr->next == NULL) {
		cout << "Data not Found\n";
		return;
	}
	Node<Type>* q = ptr->next;
	ptr->next = q->next;
	delete(q);
}
/*
-updateStudentInfo function is used to update a particular node in the list if it exists
-takes input from the user as string fullName double GPA and int level
-if the list is empty an error message is printed to the user and the function is terminated
-if not a pointer is intialzed to the head of the list to search for that student node using a while loop stopping right
at the node we wish to update
-the node data variable is then modified to carry the updated info passed to the function
*/
template <class Type>
void Linked_List<Type>::updateStudentInfo(string fullName, double GPA, int level) {
	if (head == NULL) {
		cout << "Linked List is empty\n";
		return;
	}
	Node<Type>* ptr = head;
	while (ptr != NULL && ptr->data.fullName != fullName) {
		ptr = ptr->next;
	}
	if (ptr == NULL) {
		return;
	}
	ptr->data.fullName = fullName;
	ptr->data.GPA = GPA;
	ptr->data.level = level;

}
/*
-studentSeach function is used to search the list for a particular student node using the student fullName
-studentSeach function is used to return a Student obj that carries the node we are searching for
-a pointer is intialzed to the head of the list to search for that student node using a while loop
-if the student node doesn't exist an error message is printed to the user and the function is to be terminated
-if not the student data is returned to the user
*/
template <class Type>
Student Linked_List<Type>::studentSearch(string fullName) {
	Node<Type>* ptr = head;
	while (ptr != NULL && ptr->data.fullName != fullName) {
		ptr = ptr->next;
	}
	if (ptr == NULL) {
		cout << "Student does'nt exist\n";
		Student obj("", 0, 0);
		return obj;
	}
	return ptr->data;
}
/*
-isValidFullName function is used to check the validity of the fullName entered by the user
-a fullName is invalid if it contains a special character or if it includes more or less than two name
-a for loop is used to check if the string contains a special character in it or not
-and then using the find_first_not_of and find_last_not_of function is used to determine the boundaries on which we are checking
the spaces in between indicating the validity of the fullName
*/
bool isValidFullName(string fullName) {
	for (int i = 0; i < fullName.length(); i++)
	{
		if (!isalpha(fullName[i]) && fullName[i] != ' ') {
			cout << "Student Full Name Can Not Include Special Characters\n";
			return false;
		}
	}
	int numOfSpaces = 0;
	size_t start = fullName.find_first_not_of(' ');
	size_t end = fullName.find_last_not_of(' ');
	for (size_t i = start; i <= end; i++)
	{
		if (fullName[i] == ' ') {
			numOfSpaces++;
		}
	}
	if (numOfSpaces != 1) {
		cout << "Student Full Name Must Include First And Last Name\n";
		return false;
	}
	return true;
}
/*
-isValidGPA function is used to check if the GPA entered by the user is valid or not
-isValidGPA function return a boolean value based on the validity of the GPA entered by the user
-GPA is only valid if it is between 0 and 4
*/
bool isValidGPA(double GPA) {
	if (GPA < 0 || GPA > 4)
		return false;
	return true;
}
/*
-isValidLevel function is used to check if the level entered by the user is valid or not
-isValidLevel function return a boolean value based on the validity of the Level entered by the user
-Level is only valid if it is between 1 and 4
*/
bool isValidLevel(int level) {
	if (level < 1 || level > 4)
		return false;
	return true;
}
/*
-trimString function is used to transform the string into a special format that we would be using through out the application
-trimString function returns a transformed string of the input entered by the user
-trim string takes a string parameter named dummyFullName that would be then transformed
-student fullName is seperated into two names first name and last name
-only the first letter in each one should be upperCase and all other letters should be lowerCase
-WHITESPACE varibale is used to gather type of spaces that we would remvoe from the start or the end of input
-first we start by trimming the right side of the function and storing that value in a string that would be later operated on
-an erase function is used to trim all spaces after the last letter that is not a space using find_last_not_of function
-then we trim the left side of the string using erase function the only differnce is that we start erasing from 0 to
the first charcter that is not a white space using the find_first_not_of function
-the string is then to be transformed into lowed case using transform function that is built in the algorithm library
-we then seach for the first letter in the last name and the first letter in each the first and the last name is to 
be transformed into uppercase
*/
string trimString(string dummyFullName) {
	string WHITESPACE = " \n\r\t\f\v";
	string rightTrim = dummyFullName.erase(dummyFullName.find_last_not_of(WHITESPACE) + 1);
	string leftTrim = rightTrim.erase(0, rightTrim.find_first_not_of(WHITESPACE));
	string fullName = leftTrim;
	transform(fullName.begin(), fullName.end(), fullName.begin(), ::tolower);
	int space = fullName.find(' ');
	int upperCaseLetter = space + 1;
	if (space) {
		fullName[upperCaseLetter] = toupper(fullName[upperCaseLetter]);
		fullName[0] = toupper(fullName[0]);
	}
	return fullName;
}

void main() {
	/*
	-studentDataStore is an object of the single linked list that we would be using to store student data
	*/
	Linked_List<Student> studentDataStore;
	/*
	-do while loop is used to show a menu to the user to choose the operation the user would preform and to stay in the menu
	unless the user wants to exit the program
	-a choice variable is used to take input from the user upon which the program would switch among the following cases
	*/
	int choice = 0;
	do {
		/*
		-cin.sync() function is used to sync input entered by the user and help use getline in the do while loop
		*/
		cin.sync();
		cout << "Student System\n1- Add Student\n2- DeleteStudent\n3- Update Student\n4- Search for Student\n5- Exit\n";
		cin >> choice;
		/*
		-if the user choice was to add a student then the following code would be executed
		*/
		if (choice == 1) {
			/*
			-string dummyFullName, double GPA, and int level is used to store input entered by the user
			*/
			string dummyFullName;
			double GPA = 0;
			int level = 0;
			cout << "Enter Student Full Name: ";
			/*
			-getline(cin >> ws, string) is used to help using getline in a do while loop
			-the input entered by the user is to be trimmed and transformed into the application format
			*/
			getline(cin >> ws, dummyFullName);
			string fullName = trimString(dummyFullName);
			if (!isValidFullName(fullName)) {
				cout << "Student Full Name is not Valid\n";
				continue;
			}
			/*
			-user input is to be checked using isValidForOperation to determine if the entered name exists in the list or not
			-if isValidForOperation is true the program would exit that if statement and continue in the loop
			-if it doesn't exist in the list the user would continue to enter the student data and the data would be store in the lsit
			*/
			if (studentDataStore.isValidForOperation(fullName)) {
				cout << "Student " << fullName << " already exists\n";
				continue;
			}
			/*
			-if the entered GPA was not valid an error message would be printed to the user and the program would exit 
			the if block to continue the do while loop
			*/
			cout << "Enter Student GPA: ";
			cin >> GPA;
			if (!isValidGPA(GPA)) {
				cout << "Invalid GPA ( 0 <= GPA <= 4)\n";
				continue;
			}
			/*
			-if the entered level was not valid an error message would be printed to the user and the program would exit
			the if block to continue the do while loop
			*/
			cout << "Enter Student Level: ";
			cin >> level;
			if (!isValidLevel(level)) {
				cout << "Invalid Level ( 1 <= Level <= 4)\n";
				continue;
			}
			/*
			-insertFirst function is used to store students in the list as it has a big O(1) and the order in the list would not matter
			*/
			Student student(fullName, GPA, level);
			studentDataStore.insertFirst(student);
			cout << "Student " << fullName << " has been added successfully\n";
		}
		/*
		-if the user choice was to delete a student then the following code would be executed
		*/
		if (choice == 2) {
			string dummyFullName;
			cout << "Enter student full name you want to delete: ";
			getline(cin >> ws, dummyFullName);
			string fullName = trimString(dummyFullName);
			if (!isValidFullName(fullName)) {
				cout << "Student Full Name is not Valid\n";
				continue;
			}
			if (!studentDataStore.isValidForOperation(fullName)) {
				cout << "Student " << fullName << " doesn't exist\n";
				continue;
			}
			/*
			-if the entered input from the user is valid then the student node would be deleted using the removeStudent function
			*/
			studentDataStore.removeStudent(fullName);
			cout << "Student " << fullName << " has been deleted successfully\n";
		}
		/*
		-if the user choice was to update a student data then the following code would be executed
		*/
		if (choice == 3) {
			string dummyFullName;
			double GPA;
			int level;
			cout << "Enter student full name to update: ";
			getline(cin >> ws, dummyFullName);
			string fullName = trimString(dummyFullName);
			if (!isValidFullName(fullName)) {
				cout << "Student Full Name is not Valid\n";
				continue;
			}
			if (!studentDataStore.isValidForOperation(fullName)) {
				cout << "Student " << fullName << " doesn't exist\n";
				continue;
			}
			cout << "Enter Student GPA: ";
			cin >> GPA;
			if (!isValidGPA(GPA)) {
				cout << "Invalid GPA ( 0 <= GPA <= 4)\n";
				continue;
			}
			cout << "Enter Student Level: ";
			cin >> level;
			if (!isValidLevel(level)) {
				cout << "Invalid Level ( 1 <= Level <= 4)\n";
				continue;
			}
			/*
			-if the entered input from the user is valid then the student node would be deleted using the removeStudent function
			*/
			studentDataStore.updateStudentInfo(fullName, GPA, level);
			cout << "Student " << fullName << " has been updated successfully\n";
		}
		/*
		-if the user choice was to search for a student data then the following code would be executed
		*/
		if (choice == 4) {
			string dummyFullName;
			cout << "Enter Student Full Name to search for: ";
			getline(cin >> ws, dummyFullName);
			string fullName = trimString(dummyFullName);
			if (!isValidFullName(fullName)) {
				cout << "Student Full Name is not Valid\n";
				continue;
			}
			if (!studentDataStore.isValidForOperation(fullName)) {
				cout << "Student " << fullName << " doesn't exist\n";
				continue;
			}
			/*
			-if the student data was found the student data would be printed to the user
			*/
			Student student = studentDataStore.studentSearch(fullName);
			cout << "Full Name: " << student.fullName << endl;
			cout << "GPA: " << student.GPA << endl;
			cout << "Level: " << student.level << endl;

		}
		/*
		-if the user choice was 5 which is to quit the do while loop and the program would exit the do while loop
		*/
	} while (choice != 5);
	cout << "Thank you for you time\n";
}