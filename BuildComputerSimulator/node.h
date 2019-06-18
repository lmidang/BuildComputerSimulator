#pragma once
#include <iostream>

template <typename ItemType>
class Node {
private:
	// The data stored in this node
	ItemType data;

	// A pointer to the next node
	Node<ItemType> *pNext;

public:
	// Default constructor
	Node();

	// Constructor that takes data
	Node(const ItemType &);

	// Constructor that takes data and a pointer to the next node
	Node(const ItemType &, Node<ItemType> *);

	// Getters
	ItemType getData() const;
	Node<ItemType> * getNext() const;

	// Setters
	void setData(const ItemType &);
	void setNext(Node<ItemType> *);

	// Overloaded insertion operator
	template <typename ItemType>
	friend std::ostream & operator <<(std::ostream &, const Node<ItemType> &);
};

template <typename ItemType>
Node<ItemType>::Node() : pNext(nullptr) {}

template <typename ItemType>
Node<ItemType>::Node(const ItemType &d) :
	data(d), pNext(nullptr) {}

template <typename ItemType>
Node<ItemType>::Node(const ItemType &d, Node<ItemType> *pNextNode) :
	data(d), pNext(pNextNode) {}

template <typename ItemType>
ItemType Node<ItemType>::getData() const {
	return data;
}

template <typename ItemType>
Node<ItemType> * Node<ItemType>::getNext() const {
	return pNext;
}

template <typename ItemType>
void Node<ItemType>::setData(const ItemType &d) {
	data = d;
}

template <typename ItemType>
void Node<ItemType>::setNext(Node<ItemType> *pNext) {
	this->pNext = pNext;
}

template <typename ItemType>
std::ostream & operator <<(std::ostream &stream, const Node<ItemType> &node) {
	return stream << node.data << ' ';
}