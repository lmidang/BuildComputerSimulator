/*
Worked on by Lynn Dang
*/

#pragma once
#include "singly_linked_list.h"

template <typename ItemType>
class Queue : protected SinglyLinkedList<ItemType> {
public:
	// Default constructor
	Queue();

	// Copy constructor
	Queue(const Queue<ItemType> &);

	// Virtual destructor
	virtual ~Queue();

	// Returns whether or not this queue is empty
	bool isEmpty() const;

	// Returns the data in the front node of this queue
	ItemType front() const;

	// Returns the data in the rear of this queue
	ItemType rear() const;

	// Enqueue a new node with the specified data to the back of this queue
	void enqueue(const ItemType &);

	// Dequeue the node at the front of this queue
	void dequeue();

	// Overloaded assignment operator
	Queue<ItemType> & operator =(const Queue<ItemType> &);

	// Overloaded insertion operator
	template <typename ItemType>
	friend std::ostream & operator <<(std::ostream &, const Queue<ItemType> &);
};

template <typename ItemType>
Queue<ItemType>::Queue() {}

template <typename ItemType>
Queue<ItemType>::Queue(const Queue<ItemType> &queue) : SinglyLinkedList<ItemType>(queue) {}

template <typename ItemType>
Queue<ItemType>::~Queue() {}

template <typename ItemType>
bool Queue<ItemType>::isEmpty() const {
	return SinglyLinkedList<ItemType>::isEmpty();
}

/*
Pseudocode:

- Make sure the queue isn't empty.
- Returns the data in the front node of the queue.
*/
template <typename ItemType>
ItemType Queue<ItemType>::front() const {
	if (isEmpty())
		throw "Queue is empty.";

	return this->getDataAt(0);
}

/*
Pseudocode:

- Make sure the queue isn't empty.
- Returns the data in the rear node of the queue.
*/
template <typename ItemType>
ItemType Queue<ItemType>::rear() const {
	if (isEmpty())
		throw "Queue is empty.";

	return this->pTail->getData();
}

/*
Pseudocode:

- Insert a new node with the specified data into the first index of the queue.
*/
template <typename ItemType>
void Queue<ItemType>::enqueue(const ItemType &data) {
	if (this->getCount() == 0)
		this->insertAt(0, data);
	else {
		Node<ItemType> *newNode = new Node<ItemType>(data);
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
template <typename ItemType>
void Queue<ItemType>::dequeue() {
	if (isEmpty())
		throw "Queue is empty.";

	this->deleteAt(0);
}

// Overloaded assignment operator
template <typename ItemType>
Queue<ItemType> & Queue<ItemType>::operator =(const Queue<ItemType> &queue) {
	SinglyLinkedList<ItemType>::operator =(queue);

	return *this;
}

/*
Pseudocode:

- Output this node's data to the specified stream.
*/
template <typename ItemType>
std::ostream & operator <<(std::ostream &stream, const Queue<ItemType> &queue) {
	return stream << static_cast<SinglyLinkedList<ItemType>>(queue);
}