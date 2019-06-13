#pragma once
#include <iostream>

template <typename T>
class Node {
private:
	// The data stored in this node
	T data;

	// A pointer to the next node
	Node<T> *pNext;

public:
	// Default constructor
	Node();

	// Constructor that takes data
	Node(const T &);

	// Constructor that takes data and a pointer to the next node
	Node(const T &, Node<T> *);

	// Getters
	T getData() const;
	Node<T> * getNext() const;

	// Setters
	void setData(const T &);
	void setNext(Node<T> *);

	// Overloaded insertion operator
	template <typename T>
	friend std::ostream & operator <<(std::ostream &, const Node<T> &);
};

template <typename T>
Node<T>::Node() : pNext(nullptr) {}

template <typename T>
Node<T>::Node(const T &d) :
	data(d), pNext(nullptr) {}

template <typename T>
Node<T>::Node(const T &d, Node<T> *pNextNode) :
	data(d), pNext(pNextNode) {}

template <typename T>
T Node<T>::getData() const {
	return data;
}

template <typename T>
Node<T> * Node<T>::getNext() const {
	return pNext;
}

template <typename T>
void Node<T>::setData(const T &d) {
	data = d;
}

template <typename T>
void Node<T>::setNext(Node<T> *pNext) {
	this->pNext = pNext;
}

template <typename T>
std::ostream & operator <<(std::ostream &stream, const Node<T> &node) {
	return stream << node.data << ' ';
}