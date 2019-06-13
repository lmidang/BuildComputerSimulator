/**
	This class is the Binary Node ADT class
*/

#pragma once

#ifndef _BINARY_NODE_H_
#define _BINARY_NODE_H_

#include "node.h"

template <class ItemType>
class BinaryNode : public Node<ItemType> {
	BinaryNode<ItemType> *pRightChildPtr;
	BinaryNode<ItemType> *pLeftChildPtr;
public:
	BinaryNode();	// constructor
	BinaryNode(const ItemType&);	// constructor with data but no next pointer
	BinaryNode(const ItemType&, BinaryNode<ItemType>*, BinaryNode<ItemType>*);		// constructor with data and next pointer
	BinaryNode(const BinaryNode<ItemType>&);	// copy constructor
	virtual ~BinaryNode();	// destructor

	// mutators
	/** sets left child pointer
	@pre none
	@post leftChildPtr set
	*/
	void setLeftChildPtr(BinaryNode<ItemType>*);
	/** sets right child pointer
	@pre none
	@post righttChildPtr set
	*/
	void setRightChildPtr(BinaryNode<ItemType>*);

	// accessors
	BinaryNode<ItemType>* getLeftChildPtr();
	BinaryNode<ItemType>* getRightChildPtr();

	/** returns whether the Node is a leaf
	@pre none
	@post checks whether Node is a leaf
	*/
	bool isLeaf();

	/** Returns number of children
	@pre none
	@post returns number of children
	*/
	int getNumChildren();

	/** overloads output operator */
	template <typename T>
	friend std::ostream& operator<<(std::ostream&, BinaryNode<T>&);
};

#include "BinaryNode.cpp"

#endif