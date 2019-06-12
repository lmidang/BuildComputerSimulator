#pragma once
#include "singly_linked_list.h"

template <typename T>
class Queue : protected SinglyLinkedList<T> {
public:
	// Default constructor
	Queue();

	// Copy constructor
	Queue(const Queue<T> &);

	// Virtual destructor
	virtual ~Queue();

	// Returns whether or not this queue is empty
	bool isEmpty() const;

	// Returns the data in the front node of this queue
	T front() const;

	// Returns the data in the rear of this queue
	T rear() const;

	// Enqueue a new node with the specified data to the back of this queue
	void enqueue(const T &);

	// Dequeue the node at the front of this queue
	void dequeue();

	// Overloaded assignment operator
	Queue<T> & operator =(const Queue<T> &);

	// Overloaded insertion operator
	template <typename T>
	friend std::ostream & operator <<(std::ostream &, const Queue<T> &);
};

template <typename T>
Queue<T>::Queue() {}

template <typename T>
Queue<T>::Queue(const Queue<T> &queue) : SinglyLinkedList<T>(queue) {}

template <typename T>
Queue<T>::~Queue() {}

template <typename T>
bool Queue<T>::isEmpty() const {
	return SinglyLinkedList<T>::isEmpty();
}

/*
Pseudocode:

- Make sure the queue isn't empty.
- Returns the data in the front node of the queue.
*/
template <typename T>
T Queue<T>::front() const {
	if (isEmpty())
		throw "Queue is empty.";

	return this->getDataAt(0);
}

/*
Pseudocode:

- Make sure the queue isn't empty.
- Returns the data in the rear node of the queue.
*/
template <typename T>
T Queue<T>::rear() const {
	if (isEmpty())
		throw "Queue is empty.";

	return this->pTail->getData();
}

/*
Pseudocode:

- Insert a new node with the specified data into the first index of the queue.
*/
template <typename T>
void Queue<T>::enqueue(const T &data) {
	if (this->getCount() == 0)
		this->insertAt(0, data);
	else {
		Node<T> *newNode = new Node<T>(data);
		this->pTail->setNext(newNode);
		this->pTail = newNode;
		this->count++;
	}
}

/*
Pseudocode:

- Make sure the queue isn't empty.
- Delete the node at the first index of the queue.
*/
template <typename T>
void Queue<T>::dequeue() {
	if (isEmpty())
		throw "Queue is empty.";

	this->deleteAt(0);
}

// Overloaded assignment operator
template <typename T>
Queue<T> & Queue<T>::operator =(const Queue<T> &queue) {
	SinglyLinkedList<T>::operator =(queue);

	return *this;
}

/*
Pseudocode:

- Output this node's data to the specified stream.
*/
template <typename T>
std::ostream & operator <<(std::ostream &stream, const Queue<T> &queue) {
	return stream << static_cast<SinglyLinkedList<T>>(queue);
}