#pragma once
#include "node.h"

template <typename ItemType>
class SinglyLinkedList {
private:
	// Makes a deep copy of another singly linked list
	void copyFrom(const SinglyLinkedList<ItemType> &);

	// Returns the node at the specified index (no bounds checking)
	Node<ItemType> * getNodeAt(size_t) const;

protected:
	// Pointers to the first and last node in this list, respectively
	Node<ItemType> *pHead, *pTail;

	// The number of nodes in this list
	size_t count;

public:
	// Default constructor
	SinglyLinkedList();

	// Copy constructor
	SinglyLinkedList(const SinglyLinkedList<ItemType> &);

	// Virtual destructor
	virtual ~SinglyLinkedList();

	// Returns the number of nodes in this list
	size_t getCount() const;

	// Returns whether or not this list is empty
	bool isEmpty() const;

	// Returns the data at the specified index (has bounds checking)
	ItemType getDataAt(size_t) const;

	// Sets the data of the node at the specified index
	void setDataAt(size_t, const ItemType &);

	// Creates a new node with the specified data and inserts it at the specified index
	void insertAt(size_t, const ItemType &);

	// Deletes the node at the specified index
	void deleteAt(size_t);

	// Clear the list, deleting every node
	void clear();

	// Overloaded assignment operator
	SinglyLinkedList<ItemType> & operator =(const SinglyLinkedList<ItemType> &);

	// Overloaded insertion operator
	template <typename ItemType>
	friend std::ostream & operator <<(std::ostream &, const SinglyLinkedList<ItemType> &);
};

template <typename ItemType>
SinglyLinkedList<ItemType>::SinglyLinkedList() : pHead(nullptr), pTail(nullptr), count(0) {}

template <typename ItemType>
SinglyLinkedList<ItemType>::SinglyLinkedList(const SinglyLinkedList<ItemType> &list) : pHead(nullptr), pTail(nullptr), count(0) {
	copyFrom(list);
}

template <typename ItemType>
SinglyLinkedList<ItemType>::~SinglyLinkedList() {
	clear();
}

/*
Pseudocode:

- If the first node in the original list isn't nullptr:
	- Create a new node with the same data as the original list's head, and set it to this lists's head.

	- Loop through the rest of the original list:
		- Create a new node.
		- Copy the data from the original list into the new node.
		- Link that new node to this list.
		- Increment count.

	- Set the tail to point to the end of the list.
*/
template <typename ItemType>
void SinglyLinkedList<ItemType>::copyFrom(const SinglyLinkedList<ItemType> &list) {
	clear();

	Node<ItemType> *pOrigNode = list.pHead;

	if (pOrigNode != nullptr) {
		// Copy the first node
		pHead = new Node<ItemType>(pOrigNode->getData());

		// Point to the first node
		Node<ItemType> *pCurrNode = pHead;

		pOrigNode = pOrigNode->getNext();

		count++;

		// Copy the remaining nodes
		while (pOrigNode != nullptr) {
			pCurrNode->setNext(new Node<ItemType>(pOrigNode->getData()));

			pCurrNode = pCurrNode->getNext();
			pOrigNode = pOrigNode->getNext();

			count++;
		}

		pTail = pCurrNode;
	}
}

template <typename ItemType>
size_t SinglyLinkedList<ItemType>::getCount() const {
	return count;
}

template <typename ItemType>
bool SinglyLinkedList<ItemType>::isEmpty() const {
	return !count;
}

/*
Pseudocode:

- Loop through the list until reaching the node at the specified index.
- Return that node.
*/
template <typename ItemType>
Node<ItemType> * SinglyLinkedList<ItemType>::getNodeAt(size_t index) const {
	Node<ItemType> *pCurrNode = pHead;

	for (size_t i = 0; i < index; i++)
		pCurrNode = pCurrNode->getNext();

	return pCurrNode;
}

template <typename ItemType>
ItemType SinglyLinkedList<ItemType>::getDataAt(size_t index) const {
	if (index < 0 || index >= count)
		throw "Index is out of range.";

	return getNodeAt(index)->getData();
}

template <typename ItemType>
void SinglyLinkedList<ItemType>::setDataAt(size_t index, const ItemType &data) {
	if (index < 0 || index >= count)
		throw "Index is out of range.";

	getNodeAt(index)->setData(data);
}

/*
Pseudocode:

- Check to see that the specified index is between the indices of the first and
last elements, inclusive, or that the index is equal to the index of the last
element plus one.
- Create a new node with the specified data.

- If the specified index is equal to the index of the first element:
	- Set the new node to point to the current head node.
	- Set the head to be the new node.

- Otherwise:
	- Set the new node to point to the node that will be after it.
	- Set the previous node to point to the new node.
	- If the new node is at the end of the list:
		- Set the tail to be the new node.

- Increment count.
*/
template <typename ItemType>
void SinglyLinkedList<ItemType>::insertAt(size_t index, const ItemType &data) {
	if (index < 0 || index > count)
		throw "Index is out of range.";

	Node<ItemType> *pNewNode = new Node<ItemType>(data);

	if (index == count)
		pTail = pNewNode;

	// Insert new node to beginning of linked list
	if (index == 0) {
		pNewNode->setNext(pHead);
		pHead = pNewNode;
	}
	// Insert new node to middle or end of linked list
	else {
		// Get node that will be before new node
		Node<ItemType> *pPrevNode = getNodeAt(index - 1);

		pNewNode->setNext(pPrevNode->getNext());
		pPrevNode->setNext(pNewNode);
	}

	count++;
}

/*
Pseudocode:

- Check to see that the specified index is between the indices of the first and
last elements, inclusive.

- If the specified index is equal to the index of the first element:
	- Set the head to the node directly after it.

- Otherwise:
	- Set the node before the one to delete to point to the node after the one to delete.
	- If the tail is to be deleted:
		- Set the tail to the previous node.

- Delete the node at the specified index.
- Set the node to nullptr.
- Decrement count.
*/
template <typename ItemType>
void SinglyLinkedList<ItemType>::deleteAt(size_t index) {
	if (index < 0 || index >= count)
		throw "Index is out of range.";

	Node<ItemType> *pCurNode;

	// Delete the first node of the linked list
	if (index == 0) {
		pCurNode = pHead;
		pHead = pHead->getNext();
	}
	// Delete a node in the middle or end of the linked list
	else {
		// Get node that is before the one to delete
		Node<ItemType> *pPrevNode = getNodeAt(index - 1);

		pCurNode = pPrevNode->getNext();

		pPrevNode->setNext(pCurNode->getNext());

		if (index == count - 1)
			pTail = pPrevNode;
	}

	delete pCurNode;
	pCurNode = nullptr;

	count--;
}

/*
Pseudocode:

- While the list still contains nodes:
	- Delete the first node.
*/
template <typename ItemType>
void SinglyLinkedList<ItemType>::clear() {
	while (!isEmpty())
		deleteAt(0);
}

template <typename ItemType>
SinglyLinkedList<ItemType> & SinglyLinkedList<ItemType>::operator =(const SinglyLinkedList<ItemType> &list) {
	copyFrom(list);

	return *this;
}

/*
Pseudocode:

- Loop through the linked list:
	- Output each node to the specified stream, using the node's overloaded insertion operator.
*/
template <typename ItemType>
std::ostream & operator <<(std::ostream &stream, const SinglyLinkedList<ItemType> &list) {
	Node<ItemType> *pNode = list.pHead;

	while (pNode != nullptr) {
		stream << *pNode;
		pNode = pNode->getNext();
	}

	return stream;
}