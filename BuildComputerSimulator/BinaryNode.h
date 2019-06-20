/**
	This class is the Binary Node ADT class
	Worked on by Lynn Dang
*/

#pragma once

#ifndef _BINARY_NODE_H_
#define _BINARY_NODE_H_

#include "node.h"

template <class ItemType, typename KeyType>
class BinaryNode : public Node<ItemType> {
	BinaryNode<ItemType, KeyType> *pRightChildPtr;
	BinaryNode<ItemType, KeyType> *pLeftChildPtr;
	KeyType key;
public:
	BinaryNode();	// constructor
	BinaryNode(const ItemType&, const KeyType&);	// constructor with data but no next pointer
	BinaryNode(const ItemType&, const KeyType&, BinaryNode<ItemType, KeyType>*, BinaryNode<ItemType, KeyType>*);		// constructor with data and next pointer
	BinaryNode(const BinaryNode<ItemType, KeyType>&);	// copy constructor
	virtual ~BinaryNode();	// destructor

	// mutators
	/** sets left child pointer
	@pre none
	@post leftChildPtr set
	*/
	void setLeftChildPtr(BinaryNode<ItemType, KeyType>*);
	/** sets right child pointer
	@pre none
	@post righttChildPtr set
	*/
	void setRightChildPtr(BinaryNode<ItemType, KeyType>*);

	// accessors
	BinaryNode<ItemType, KeyType>* getLeftChildPtr();
	BinaryNode<ItemType, KeyType>* getRightChildPtr();

	/** returns whether the Node is a leaf
	@pre none
	@post checks whether Node is a leaf
	*/
	bool isLeaf();

	void setBinaryData(const ItemType &, const KeyType&);
	KeyType &getKey();

	/** Returns number of children
	@pre none
	@post returns number of children
	*/
	int getNumChildren();

	/** overloads output operator */
	template <typename ItemType>
	friend std::ostream& operator<<(std::ostream&, BinaryNode<ItemType, KeyType>&);
};

#include "BinaryNode.h"

// default constructor, childptrs set to nullptr
template <class ItemType, typename KeyType> BinaryNode<ItemType, KeyType>::BinaryNode() : Node<ItemType>() {
	pRightChildPtr = nullptr;
	pLeftChildPtr = nullptr;
}

// constructor, childptrs set to nullptr
template <class ItemType, typename KeyType> BinaryNode<ItemType, KeyType>::BinaryNode(const ItemType& item, const KeyType &keyD) : Node<ItemType>(item) {
	pRightChildPtr = nullptr;
	pLeftChildPtr = nullptr;
	key = keyD;
}

// default constructor, childptrs set respectively
template <class ItemType, typename KeyType> BinaryNode<ItemType, KeyType>::BinaryNode(const ItemType& item, const KeyType &keyD, BinaryNode<ItemType, KeyType>* rightChildPtr, BinaryNode<ItemType, KeyType>* leftChildPtr) : Node<ItemType, KeyType>(item) {
	pRightChildPtr = rightChildPtr;
	pLeftChildPtr = leftChildPtr;
	key = keyD;
}

// copy constructor
template <class ItemType, typename KeyType> BinaryNode<ItemType, KeyType>::BinaryNode(const BinaryNode<ItemType, KeyType>& bN) : Node<ItemType, KeyType>(bN) {
	pRightChildPtr = new BinaryNode<ItemType, KeyType>(bN.rightChildPtr);
	pLeftChildPtr = new BinaryNode<ItemType, KeyType>(bN.leftChildPtr);
}

// destructor
template <class ItemType, typename KeyType> BinaryNode<ItemType, KeyType>::~BinaryNode() {
}

// mutators
template <class ItemType, typename KeyType>
void BinaryNode<ItemType, KeyType>::setLeftChildPtr(BinaryNode<ItemType, KeyType>* leftChild) {
	pLeftChildPtr = leftChild;
}

template <class ItemType, typename KeyType>
void BinaryNode<ItemType, KeyType>::setRightChildPtr(BinaryNode<ItemType, KeyType>* rightChild) {
	pRightChildPtr = rightChild;
}

// accessors
template <class ItemType, typename KeyType>
BinaryNode<ItemType, KeyType>* BinaryNode<ItemType, KeyType>::getLeftChildPtr() {
	return pLeftChildPtr;
}

template <class ItemType, typename KeyType>
BinaryNode<ItemType, KeyType>* BinaryNode<ItemType, KeyType>::getRightChildPtr() {
	return pRightChildPtr;
}

/** Checks whether node is leaf
@return whether node is leaf
*/
template <class ItemType, typename KeyType>
bool BinaryNode<ItemType, KeyType>::isLeaf() {
	return (getLeftChildPtr() == nullptr) && (getRightChildPtr() == nullptr);
}

/** Returns number of children
@return number of children
*/
template <class ItemType, typename KeyType>
int BinaryNode<ItemType, KeyType>::getNumChildren() {
	int num = 0;
	if (getLeftChildPtr() != nullptr) {
		num++;
	}
	if (getRightChildPtr() != nullptr) {
		num++;
	}
	return num;
}

template <class ItemType, typename KeyType>
void BinaryNode<ItemType, KeyType>::setBinaryData(const ItemType &item, const KeyType &keyD) {
	this->setData(item);
	key = keyD;
}

template <class ItemType, typename KeyType>
KeyType &BinaryNode<ItemType, KeyType>::getKey() {
	return key;
}

// ostream operator
template <typename ItemType, typename KeyType>
std::ostream& operator<<(std::ostream& os, BinaryNode<ItemType, KeyType>& bN) {
	os << bN.getData();
}


#endif