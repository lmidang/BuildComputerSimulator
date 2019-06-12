#include "BinaryNode.h"

// default constructor, childptrs set to nullptr
template <class ItemType> BinaryNode<ItemType>::BinaryNode() : Node<ItemType>() {
	pRightChildPtr = nullptr;
	pLeftChildPtr = nullptr;
}

// constructor, childptrs set to nullptr
template <class ItemType> BinaryNode<ItemType>::BinaryNode(const ItemType& item) : Node<ItemType>(item) {
	pRightChildPtr = nullptr;
	pLeftChildPtr = nullptr;
}

// default constructor, childptrs set respectively
template <class ItemType> BinaryNode<ItemType>::BinaryNode(const ItemType& item, BinaryNode<ItemType>* rightChildPtr, BinaryNode<ItemType>* leftChildPtr) : Node<ItemType>(item) {
	pRightChildPtr = rightChildPtr;
	pLeftChildPtr = leftChildPtr;
}

// copy constructor
template <class ItemType> BinaryNode<ItemType>::BinaryNode(const BinaryNode<ItemType>& bN) : Node<ItemType>(bN) {
	pRightChildPtr = new BinaryNode<ItemType>(bN.rightChildPtr);
	pLeftChildPtr = new BinaryNode<ItemType>(bN.leftChildPtr);
}

// destructor
template <class ItemType> BinaryNode<ItemType>::~BinaryNode() {
}

// mutators
template <class ItemType> 
void BinaryNode<ItemType>::setLeftChildPtr(BinaryNode<ItemType>* leftChild)  {
	pLeftChildPtr = leftChild;
}

template <class ItemType>
void BinaryNode<ItemType>::setRightChildPtr(BinaryNode<ItemType>* rightChild) {
	pRightChildPtr = rightChild;
}

// accessors
template <class ItemType>
BinaryNode<ItemType>* BinaryNode<ItemType>::getLeftChildPtr() {
	return pLeftChildPtr;
}

template <class ItemType>
BinaryNode<ItemType>* BinaryNode<ItemType>::getRightChildPtr() {
	return pRightChildPtr;
}

/** Checks whether node is leaf
@return whether node is leaf
*/
template <class ItemType>
bool BinaryNode<ItemType>::isLeaf() {
	return (getLeftChildPtr() == nullptr) && (getRightChildPtr() == nullptr);
}

/** Returns number of children
@return number of children
*/
template <class ItemType>
int BinaryNode<ItemType>::getNumChildren() {
	int num = 0;
	if (getLeftChildPtr() != nullptr) {
		num++;
	}
	if (getRightChildPtr() != nullptr) {
		num++;
	}
	return num;
}

// ostream operator
template <typename T>
std::ostream& operator<<(std::ostream& os, BinaryNode<T>& bN) {
	os << bN.getData();
}
