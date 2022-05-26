#include <iostream>
#include <string>
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

template <class H>
class Node {
public:
	H data;
	Node* next;
	Node* prev;
	Node(H val);
};
template <class H>
Node<H> ::Node(H val) {
	data = val;
	next = NULL;
	prev = NULL;
}
template <class H>
class Linked_List {
	Node<H>* head;
	Node<H>* tail;
	int size;
public:
	Linked_List();
	~Linked_List();
	void insertFirst(H val);
	void insertLast(H val);
	void insertAfter(H val, int pos);
	H removeFirst();
	H removeLast();
	H removeNode(H val);
	H search(H val);
	void display();
	int get_size() { return size; }
};

template <class H>
Linked_List<H>::Linked_List() {
	head = NULL;
	tail = NULL;
	size = 0;
}

template<class H>
Linked_List<H> :: ~Linked_List() {
	while (head != NULL) {
		H temp = removeFirst();
	}
}
template<class H>
void Linked_List<H>::insertFirst(H val) {
	size++;
	Node<H>* newNode = new Node<H>(val);
	if (head == NULL) {
		head = tail = newNode;
	}
	else {
		newNode->next = head;
		head->prev = newNode;
		head = newNode;
	}
}
template <class H>
void Linked_List<H> ::insertLast(H val) {
	size++;
	Node<H>* newNode = new Node<H>(val);
	if (head == NULL) {
		head = tail = newNode;
	}
	else {
		tail->next = newNode;
		newNode->prev = tail;
		tail = newNode;
		tail->next = NULL;
	}

}
template<class H>
void Linked_List<H> ::insertAfter(H val, int pos) {
	size++;
	Node<H>* ptr = head;
	int i = 0;
	while (ptr != NULL && i < pos){
		ptr = ptr->next;
		i++;
	}
	if (ptr == NULL || i != pos) {
		cout << "Position not found\n";
		return;
	}
	Node<H>* newNode = new Node<H>(val);
	if (ptr == tail) {
		newNode->prev = tail;
		tail->next = newNode;
		tail = newNode;
	}
	else {
		Node<H>* nextNode = ptr->next;
		newNode->next = nextNode;
		newNode->prev = ptr;
		nextNode->prev = newNode;
		ptr->next = newNode;
	}
}
template <class H>
H Linked_List<H>::removeFirst() {
	size--;
	if (head == NULL) {
		cout << "List is empty\n";
		system("pause");
		exit(1);
	}
	else {
		H val = head->data;
		if (head->next == NULL) {
			delete(head);
			head = tail = NULL;
		}
		else {
			Node<H>* ptr = head;
			head = ptr->next;
			delete(ptr);
		}
		return val;
	}
}
template <class H>
H Linked_List<H>::removeLast() {
	size--;
	if (head == NULL) {
		cout << "List is empty\n";
		system("pause");
		exit(1);
	}
	else {
		H val = tail->data;
		if (head->next == NULL) {
			delete(head);
			head = tail = NULL;
		}
		else {
			Node<H>* ptr = tail;
			tail = tail->prev;
			tail->next = NULL;
			delete(ptr);
		}
		
		return val;
	}
}
template <class H>
void Linked_List<H>::display() {
	cout << "The List is: ";
	Node<H>* ptr = head;
	while (ptr != NULL) {
		cout << ptr->data << " | ";
		ptr = ptr->next;
	}
	cout << endl;
}

void main() {
	Linked_List<int> obj1;
	obj1.insertFirst(4);
	obj1.display();
	obj1.insertFirst(1);
	obj1.display();
	obj1.insertLast(5);
	obj1.display();
	obj1.removeFirst();
	obj1.display();
	obj1.insertLast(10);
	obj1.display();
	obj1.removeLast();
	obj1.display();
	obj1.removeLast();
	obj1.display();
	obj1.removeLast();
	obj1.display();
	obj1.insertFirst(1);
	obj1.insertFirst(2);
	obj1.insertFirst(3);
	obj1.insertAfter(10, 1);
	obj1.display();
	cout << obj1.get_size();
}