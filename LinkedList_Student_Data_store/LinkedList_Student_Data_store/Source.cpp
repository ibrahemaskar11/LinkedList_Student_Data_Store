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

template <class Type>
class Node {
public:
	Type data;
	Node* next;
	Node* prev;
	Node(Type val);
};
template <class Type>
Node<Type>::Node(Type val) {
	data = val;
	next = NULL;
	prev = NULL;
}
template <class Type>
class Linked_List {
	Node<Type>* head;
	Node<Type>* tail;
	int size;
public:
	Linked_List();
	~Linked_List();
	void insertFirst(Type val);
	void insertLast(Type val);
	void insertAfter(Type val, int pos);
	Type removeFirst();
	Type removeLast();
	Type removeNode(Type val);
	Type search(Type val);
	void display();
	int get_size() { return size; }
};

template <class Type>
Linked_List<Type>::Linked_List() {
	head = NULL;
	tail = NULL;
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
		head = tail = newNode;
	}
	else {
		newNode->next = head;
		head->prev = newNode;
		head = newNode;
	}
}
template <class Type>
void Linked_List<Type> ::insertLast(Type val) {
	size++;
	Node<Type>* newNode = new Node<Type>(val);
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
template<class Type>
void Linked_List<Type> ::insertAfter(Type val, int pos) {
	size++;
	Node<Type>* ptr = head;
	int i = 0;
	while (ptr != NULL && i < pos){
		ptr = ptr->next;
		i++;
	}
	if (ptr == NULL || i != pos) {
		cout << "Position not found\n";
		return;
	}
	Node<Type>* newNode = new Node<Type>(val);
	if (ptr == tail) {
		newNode->prev = tail;
		tail->next = newNode;
		tail = newNode;
	}
	else {
		Node<Type>* nextNode = ptr->next;
		newNode->next = nextNode;
		newNode->prev = ptr;
		nextNode->prev = newNode;
		ptr->next = newNode;
	}
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
			head = tail = NULL;
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
		Type val = tail->data;
		if (head->next == NULL) {
			delete(head);
			head = tail = NULL;
		}
		else {
			Node<Type>* ptr = tail;
			tail = tail->prev;
			tail->next = NULL;
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