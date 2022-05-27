#include <iostream>
#include <string>
#include<string.h>
using namespace std;

class Student {
public:
	string fullName;
	double GPA;
	int level;
	Student();
	Student(string fullName, double GPA, int level);
	Student(const Student& old_obj);
};
Student::Student() {
	fullName = "";
	GPA = 0;
	level = 0;
}
Student::Student(string fullName, double GPA, int level) {
	this->fullName = fullName;
	this->GPA = GPA;
	this->level = level;
};

Student::Student(const Student& old_obj) {
	fullName = old_obj.fullName;
	GPA = old_obj.GPA;
	level = old_obj.level;
};

template <class Type>
class Node {
public:
	Type data;
	Node* next;
	Node(Type val);
};
template <class Type>
Node<Type>::Node(Type val) {
	data = val;
	next = NULL;
}
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
	void display();
	void updateStudentInfo(string fullName, double GPA, int level);
	Student studentSearch(string fullName);
	int get_size() { return size; }
};

template <class Type>
Linked_List<Type>::Linked_List() {
	head = NULL;
	size = 0;
}

template<class Type>
Linked_List<Type> :: ~Linked_List() {
	while (head != NULL) {
		Type temp = removeFirst();
	}
}
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
template <class Type>
void Linked_List<Type>::display() {
	cout << "The List is: ";
	Node<Type>* ptr = head;
	while (ptr != NULL) {
		cout << ptr->data << " | ";
		ptr = ptr->next;
	}
	cout << endl;
}
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
	cout << get_size();
}
template <class Type>
void Linked_List<Type>::updateStudentInfo(string fullName, double GPA, int level) {
	Node<Type>* ptr = head;
	while (ptr != NULL && ptr->data.fullName != fullName) {
		ptr = ptr->next;
	}
	ptr->data.fullName = fullName;
	ptr->data.GPA = GPA;
	ptr->data.level = level;

}
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

bool isValidFullName(string fullName) {
	for (int i = 0; i < fullName.length(); i++)
	{
		if (!isalpha(fullName[i]) && fullName[i] != ' ') {
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
		return false;
	}
	return true;
}
bool isValidGPA(double GPA) {
	if (GPA < 0 || GPA > 4)
		return false;
	return true;
}
bool isValidLevel(int level) {
	if (level < 1 || level > 4)
		return false;
	return true;
}


int main() {
	Linked_List<Student> studentDataStore;
	int choice = 5;
	do {
		cin.sync();
		cout << "Student System\n1- Add Student\n2- DeleteStudent\n3- Update Student\n4- Search for Student\n5- Exit\n";
		cin >> choice;
		if (choice == 1) {
			string firstName = "";
			string lastName = "";
			double GPA = 0;
			int level = 0;
			cout << "Enter Student Full Name to search for: ";
			cin >> firstName >> lastName;
			string fullName = firstName + " " + lastName;
			if (!isValidFullName(fullName)) {
				cout << "Student Full Name is not Valid\n";
				continue;
			}
			if (studentDataStore.isValidForOperation(fullName)) {
				cout << "Student already exists\n";
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
			Student student(fullName, GPA, level);
			studentDataStore.insertLast(student);
			cout << studentDataStore.get_size();
		}
		if (choice == 2) {
			string firstName = "";
			string lastName = "";
			cout << "Enter Student Full Name to search for: ";
			cin >> firstName >> lastName;
			string fullName = firstName + " " + lastName;
			if (!isValidFullName(fullName)) {
				cout << "Student Full Name is not Valid\n";
				continue;
			}
			if (!studentDataStore.isValidForOperation(fullName)) {
				cout << "Student doesn't exists";
				continue;
			}
			studentDataStore.removeStudent(fullName);
			cout << "Student " << fullName << " has been deleted successfully\n";
		}
		if (choice == 3) {
			string firstName;
			string lastName;
			double GPA;
			int level;
			cout << "Enter Student Full Name to update: ";
			cin >> firstName >> lastName;
			string fullName = firstName + " " + lastName;
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
			studentDataStore.updateStudentInfo(fullName, GPA, level);
			cout << "Student " << fullName << " has been updated successfully\n";
		}
		if (choice == 4) {
			string firstName;
			string lastName;
			cout << "Enter Student Full Name to search for: ";
			cin >> firstName >> lastName;
			string fullName = firstName + " " + lastName;
			if (!isValidFullName(fullName)) {
				cout << "Student Full Name is not Valid\n";
				continue;
			}
			if (!studentDataStore.isValidForOperation(fullName)) {
				cout << "Student " << fullName << " doesn't exist\n";
				continue;
			}
			Student student = studentDataStore.studentSearch(fullName);
			cout << "Full Name: " << student.fullName << endl;
			cout << "GPA: " << student.GPA << endl;
			cout << "Level: " << student.level << endl;

		}

	} while (choice != 5);
	cout << studentDataStore.get_size();
	return 0;
}