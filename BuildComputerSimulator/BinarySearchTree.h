#pragma once
/**
	This class is a Binary Search Tree class
*/

#ifndef _BINARY_SEARCH_TREE
#define _BINARY_SEARCH_TREE

#include <fstream>
#include "BinaryNode.h"
#include "queue.h"

template<class ItemType, typename KeyType>
class BinarySearchTree
{
protected:
	BinaryNode<ItemType, KeyType>* rootPtr;
	int loadFactor = 0;

	/** Returns height
	@pre tree is not empty
	@post height of the tree is calculated recursively
	@param BinaryNode ptr to check the height
	@return height of the node
	*/
	int getHeightHelper(BinaryNode<ItemType, KeyType>*) const;
	/** Returns number of nodes
	@pre tree is not empty
	@post number of nodes in the subtree is calculated recursively
	@param BinaryNode ptr to the subtree get the number of nodes
	@return number of nodes of the subtree
	*/
	int getNumNodesHelper(BinaryNode<ItemType, KeyType>*) const;

	/** Inserts node into the subtree
	@pre none
	@post node is inserted into subtree
	@param subtree root node ptr
	@param node to insert
	@return root node to subtree
	*/
	virtual BinaryNode<ItemType, KeyType>* insertInOrder(BinaryNode<ItemType, KeyType>*, BinaryNode<ItemType, KeyType>*);

	/** Removes node by value
	@pre value exists in the tree
	@post value in the tree is removed
	@param subtree to removed from
	@param value to remove
	@param success boolean
	@return modified subtree root ptr
	*/
	virtual BinaryNode<ItemType, KeyType>* removeValue(BinaryNode<ItemType, KeyType>*, const ItemType&, const KeyType&, bool&);

	/** Removes the node
	@pre node exists
	@post node is removed
	@param node to remove
	@return modified subtree root ptr
	*/
	BinaryNode<ItemType, KeyType>* removeNode(BinaryNode<ItemType, KeyType>*);

	/** Removes the leftmost node
	@pre node exists
	@post leftmost node is removed
	@param subtree to remove leftmost node
	@return modified subtree root ptr
	*/
	BinaryNode<ItemType, KeyType>* removeLeftmostNode(BinaryNode<ItemType, KeyType>*, ItemType&, KeyType&);

	/** Returns node by item
	@pre item exists
	@post node with item value is found
	@param subtree root ptr
	@param item
	@return node ptr with item value
	*/
	virtual BinaryNode<ItemType, KeyType>* findNode(BinaryNode<ItemType, KeyType>*, ItemType&, KeyType&) const;

	/** preorder traverse recursive
	@pre tree exists
	@post tree was traversed
	@param visit() function
	@param subtree root ptr
	*/
	void preorder(void visit(const ItemType &), BinaryNode<ItemType, KeyType>*);

	/** inorder traverse recursive
	@pre tree exists
	@post tree was traversed
	@param visit() function
	@param subtree root ptr
	*/
	void inOrder(void visit(const ItemType &), BinaryNode<ItemType, KeyType>*);

	/** postorder traverse recursive
	@pre tree exists
	@post tree was traversed
	@param visit() function
	@param subtree root ptr
	*/
	void postorder(void visit(const ItemType &), BinaryNode<ItemType, KeyType>*);

	/** breadthFirst traverse
	@pre tree exists
	@post tree was traversed
	@param visit() function
	@param subtree root ptr
	*/
	void breadthFirst(void visit(const ItemType &), BinaryNode<ItemType, KeyType>*);

	void printIndented(void visit(const ItemType &), BinaryNode<ItemType, KeyType>*, int);
public:
	class NotFoundException;

	BinarySearchTree();	// default constructor
	BinarySearchTree(const ItemType&, const KeyType&);	// constructor with rootptr
	BinarySearchTree(const BinarySearchTree<ItemType, KeyType>&);	// copy constructor
	virtual ~BinarySearchTree();	// destructor
	
	// accessors
	bool isEmpty() const;
	int getHeight() const;
	int getNumberOfNodes() const;
	ItemType& getRoot();
	int getLoadFactor();
	
	/** adds to the tree
	@pre none
	@post item is added to the tree
	@param item was added
	@return success
	*/
	bool add(const ItemType&, const KeyType&);

	/** removes item from the tree
	@pre item exists
	@post item is removed
	@param item to remove
	@return success
	*/
	bool remove(const ItemType&, const KeyType&);

	// clears the tree
	void clear();

	/** checks whether item exists
	@pre none
	@post returns whether item exists
	@param item to check
	@return whether it exists
	*/
	bool contains(const ItemType&, const KeyType&) const;

	/** preorder traverse
	@pre tree isn't emptry
	@post tree was traverse from the top
	@param visit
	*/
	void preorderTraverse(void visit(const ItemType &));

	/** inOrder traverse
	@pre tree isn't emptry
	@post tree was traverse from the top
	@param visit
	*/
	void inOrderTraverse(void visit(const ItemType &));

	/** postorder traverse
	@pre tree isn't emptry
	@post tree was traverse from the top
	@param visit
	*/
	void postorderTraverse(void visit(const ItemType &));

	/** breadth first traverse
	@pre tree isn't emptry
	@post tree was traverse from the top
	@param visit
	*/
	void breadthFirstTraverse(void visit(const ItemType &));

	void printIndentedAll(void visit(const ItemType &));
};

// default constructor initializes rootptr to nullptr
template <class ItemType, typename KeyType>
BinarySearchTree<ItemType, KeyType>::BinarySearchTree()
{
	rootPtr = nullptr;
}

// constructor initializing rootptr with rootItem
template <class ItemType, typename KeyType>
BinarySearchTree<ItemType, KeyType>::BinarySearchTree(const ItemType& rootItem, const KeyType& key)
{
	rootPtr = new BinaryNode<ItemType, KeyType>(rootItem, key);
}

// copy constructor
template <class ItemType, typename KeyType>
BinarySearchTree<ItemType, KeyType>::BinarySearchTree(const BinarySearchTree<ItemType, KeyType> &bst)
{
	rootPtr = new BinaryNode<ItemType, KeyType>(bst.rootPtr->getData(), bst->getKey());
}

// destructor
template <class ItemType, typename KeyType>
BinarySearchTree<ItemType, KeyType>::~BinarySearchTree()
{
	if (!isEmpty()) {
		clear();
	}
}

// returns whether rootptr is nullptr
template <class ItemType, typename KeyType>
bool BinarySearchTree<ItemType, KeyType>::isEmpty() const
{
	return (rootPtr == nullptr);
}

/** insertInOrder
1 if subTreePtr is null
	1 return newNodePtr
2 else if (subTreePtr data is greater than newNodePtr data)
	1 set leftChildPtr to insertInOrder(subTreePtr left child, newNodePtr)
3 else
	1 set rightChildPtr to insertInOrder(subTreePtr right child, newNodePtr)
4 return subTreePtr
*/
template <class ItemType, typename KeyType>
BinaryNode<ItemType, KeyType>* BinarySearchTree<ItemType, KeyType>::insertInOrder(BinaryNode<ItemType, KeyType>* subTreePtr, BinaryNode<ItemType, KeyType>* newNodePtr)
{
	if (subTreePtr == nullptr) {
		return newNodePtr;
	}
	else if (subTreePtr->getKey() > newNodePtr->getKey())
	{
		BinaryNode<ItemType, KeyType>* tempPtr = insertInOrder(subTreePtr->getLeftChildPtr(), newNodePtr);
		loadFactor++;

		subTreePtr->setLeftChildPtr(tempPtr);
		loadFactor++;
	}
	else {
		BinaryNode<ItemType, KeyType>* tempPtr = insertInOrder(subTreePtr->getRightChildPtr(), newNodePtr);
		loadFactor++;

		subTreePtr->setRightChildPtr(tempPtr);
		loadFactor++;
	}
	return subTreePtr;
}

/** add
adds newNodePtr from newData to root tree using insertInOrder
*/
template <class ItemType, typename KeyType>
bool BinarySearchTree<ItemType, KeyType>::add(const ItemType& newData, const KeyType& keyD) {
	BinaryNode<ItemType, KeyType>* newNodePtr = new BinaryNode<ItemType, KeyType>(newData, keyD);
	loadFactor++;

	rootPtr = insertInOrder(rootPtr, newNodePtr);
	loadFactor++;
	return true;
}

// Removes a target value from a binary search tree recursively
template <class ItemType, typename KeyType>
BinaryNode<ItemType, KeyType> *BinarySearchTree<ItemType, KeyType>::removeValue(BinaryNode<ItemType, KeyType> *pSubTree, const ItemType &target, const KeyType& keyD, bool &success) {
	if (pSubTree == nullptr) {
		success = false;
		return nullptr;
	}
	else if (pSubTree->getData() == target) {
		pSubTree = removeNode(pSubTree);
		success = true;
		return pSubTree;
	}
	else if (pSubTree->getKey() > keyD) {
		BinaryNode<ItemType, KeyType> *tempPtr = removeValue(pSubTree->getLeftChildPtr(), target, keyD, success);
		pSubTree->setLeftChildPtr(tempPtr);
		return pSubTree;

	}
	else {
		BinaryNode<ItemType, KeyType> *tempPtr = removeValue(pSubTree->getRightChildPtr(), target, keyD, success);
		pSubTree->setRightChildPtr(tempPtr);
		return pSubTree;
	}
}

//removes a node from the binary search tree
//checks if node has child nodes
//if does not, delete node
template <class ItemType, typename KeyType>
BinaryNode<ItemType, KeyType> *BinarySearchTree<ItemType, KeyType>::removeNode(BinaryNode<ItemType, KeyType> *pNode) {
	bool hasLeftChild = pNode->getLeftChildPtr() != nullptr,
		hasRightChild = pNode->getRightChildPtr() != nullptr;
	
	if (!hasLeftChild && !hasRightChild) {
		delete pNode;
		pNode = nullptr;
		return pNode;
	}

	if (hasLeftChild != hasRightChild) {
		BinaryNode<ItemType, KeyType> *pChild;

		if (hasLeftChild) {
			pChild = pNode->getLeftChildPtr();
		}
		else {
			pChild = pNode->getRightChildPtr();
		}

		delete pNode;
		pNode = nullptr;
		return pChild;
	}
	else {
		ItemType newNodeData;
		KeyType keyD;
		BinaryNode<ItemType, KeyType> *tempPtr = removeLeftmostNode(pNode->getRightChildPtr(), newNodeData, keyD);
		pNode->setRightChildPtr(tempPtr);
		pNode->setBinaryData(newNodeData,keyD);
		return pNode;
	}

}

// removes leftmost
template <class ItemType, typename KeyType>
BinaryNode<ItemType, KeyType> * BinarySearchTree<ItemType, KeyType>::removeLeftmostNode(BinaryNode<ItemType, KeyType> *pSubTree, ItemType &inorderSuccessor, KeyType &inorderKey) {
	if (pSubTree->getLeftChildPtr() == nullptr) {

		inorderSuccessor = pSubTree->getData();

		inorderKey = pSubTree->getKey();

		return removeNode(pSubTree);
	}

	pSubTree->setLeftChildPtr(removeLeftmostNode(pSubTree->getLeftChildPtr(), inorderSuccessor, inorderKey));
	return pSubTree;
}

/** remove
1 removes item by removeValue(rootPtr, item, success)
2 return success
*/
template <class ItemType, typename KeyType>
bool BinarySearchTree<ItemType, KeyType>::remove(const ItemType& item, const KeyType& keyD) {
	bool success = false;
	rootPtr = removeValue(rootPtr, item, keyD, success);
	return success;
}

/** finds the node with item value
1 if subTreePtr is null, return nullptr
2 else if subTreePtr data is item, return subTreePtr
3 else if subTreePtr data is greater than item, return findNode(subTreePtr left child)
4 else return findNode(subTreePtr right child)
*/
template <class ItemType, typename KeyType>
BinaryNode<ItemType, KeyType>* BinarySearchTree<ItemType, KeyType>::findNode(BinaryNode<ItemType, KeyType>* subTreePtr, ItemType &item, KeyType &keyD) const
{
	if (subTreePtr == nullptr) {
		return nullptr;
	}
	else if (subTreePtr->getData() == item) {
		return subTreePtr;
	}
	else if (subTreePtr->getKey() > keyD) {
		return findNode(subTreePtr->getLeftChildPtr(), item, keyD);
	}
	else {
		return findNode(subTreePtr->getRightChildPtr(), item, keyD);
	}
}

/** clear
1 while rootPtr is not null, remove rootPtr
*/
template <class ItemType, typename KeyType>
void BinarySearchTree<ItemType, KeyType>::clear()
{
	while (rootPtr != nullptr) {
		rootPtr = removeNode(rootPtr);
	}
}

/** getHeightHelper
1 if subTreePtr is nullptr return 0
2 else
	1 getHeightHelper(subTreePtr leftChild)
	2 getHeightHelper(subTreePtr rightChild)
	3 get maximum of left and right child height
	4 return maximum + 1
*/
template <class ItemType, typename KeyType>
int BinarySearchTree<ItemType, KeyType>::getHeightHelper(BinaryNode<ItemType, KeyType>* subTreePtr) const
{
	if (subTreePtr == nullptr) {
		return 0;
	}
	else {
		int left = getHeightHelper(subTreePtr->getLeftChildPtr());
		int right = getHeightHelper(subTreePtr->getRightChildPtr());
		int maximum = (left > right) ? left : right;
		return 1 + maximum;
	}
}

/** getHeight
returns height of the whole tree
*/
template <class ItemType, typename KeyType>
int BinarySearchTree<ItemType, KeyType>::getHeight() const {
	return getHeightHelper(rootPtr);
}

/** getNumNodesHelper
1 if subTreePtr is nullptr return 0
2 else
	1 getNumNodesHelper(subTreePtr leftChild)
	2 getNumNodesHelper(subTreePtr rightChild)
	3 return left + right + 1
*/
template <class ItemType, typename KeyType>
int BinarySearchTree<ItemType, KeyType>::getNumNodesHelper(BinaryNode<ItemType, KeyType>* subTreePtr) const
{
	if (subTreePtr == nullptr) {
		return 0;
	}
	else {
		int left = getNumNodesHelper(subTreePtr->getLeftChildPtr());
		int right = getNumNodesHelper(subTreePtr->getRightChildPtr());
		return 1 + left + right;
	}
}

/** getNumberOfNodes
returns number of nodes from rootPtr
*/
template <class ItemType, typename KeyType>
int BinarySearchTree<ItemType, KeyType>::getNumberOfNodes() const {
	return getNumNodesHelper(rootPtr);
}

template <class ItemType, typename KeyType>
ItemType& BinarySearchTree<ItemType, KeyType>::getRoot() {
	return rootPtr->getData();
}

template <class ItemType, typename KeyType>
int BinarySearchTree<ItemType, KeyType>::getLoadFactor() {
	return loadFactor;
}

/** contains
returns whether node of item exists
*/
template <class ItemType, typename KeyType>
bool BinarySearchTree<ItemType, KeyType>::contains(const ItemType &anEntry, const KeyType &keyD) const {
	return (findNode(rootPtr, anEntry, keyD) != nullptr);
}

/** preorder
1 is treePtr is null
	1 process node
	2 preorder(left)
	3 preorder(right)
*/
template <class ItemType, typename KeyType>
void BinarySearchTree<ItemType, KeyType>::preorder(void visit(const ItemType &), BinaryNode<ItemType, KeyType>* treePtr)
{
	if (treePtr != nullptr) {
		ItemType item = treePtr->getData();
		visit(item);
		preorder(visit, treePtr->getLeftChildPtr());
		preorder(visit, treePtr->getRightChildPtr());
	}
}

/** inOrder
1 if treePtr is not null
	1 inOrder(left)
	2 process node
	3 inOrder(right)
*/
template <class ItemType, typename KeyType>
void BinarySearchTree<ItemType, KeyType>::inOrder(void visit(const ItemType &), BinaryNode<ItemType, KeyType>* treePtr)
{
	if (treePtr != nullptr) {
		inOrder(visit, treePtr->getLeftChildPtr());
		ItemType item = treePtr->getData();
		visit(item);
		inOrder(visit, treePtr->getRightChildPtr());
	}
}

/** postorder
1 if treePtr is not null
	1 postOrder(left)
	2 postOrder(right)
	3 process node
*/
template <class ItemType, typename KeyType>
void BinarySearchTree<ItemType, KeyType>::postorder(void visit(const ItemType &), BinaryNode<ItemType, KeyType>* treePtr)
{
	if (treePtr != nullptr) {
		postorder(visit, treePtr->getLeftChildPtr());
		postorder(visit, treePtr->getRightChildPtr());
		ItemType item = treePtr->getData();
		visit(item);
	}
}

/** breadthFirst
1 if treePtr is not nullptr
	1 set currentNode to rootPtr
	2 while curretNode is not nullptr
		1 process currentNode
		2 if currentNode has left child
			1 queue left child
		3 if currentNode has right child
			1 queue right child
		4 if queue is not empty
			1 set currentNode to dequeue
		5 else
			1 set currentNode to nullptr
*/
template <class ItemType, typename KeyType>
void BinarySearchTree<ItemType, KeyType>::breadthFirst(void visit(const ItemType &), BinaryNode<ItemType, KeyType>* treePtr)
{
	if (treePtr != nullptr) {
		BinaryNode<ItemType, KeyType> *currentNode = rootPtr;
		Queue<BinaryNode<ItemType, KeyType>*> bfQueue;
		while (currentNode != nullptr) {
			ItemType item = currentNode->getData();
			visit(item);
			if (currentNode->getLeftChildPtr() != nullptr) {
				bfQueue.enqueue(currentNode->getLeftChildPtr());
			}
			if (currentNode->getRightChildPtr() != nullptr) {
				bfQueue.enqueue(currentNode->getRightChildPtr());
			}
			if (!bfQueue.isQueueEmpty()) {
				currentNode = bfQueue.dequeue();
			}
			else {
				currentNode = nullptr;
			}
		}
	}
}

/** preorderTraverse
preorder traverse from rootPtr
*/
template <class ItemType, typename KeyType>
void BinarySearchTree<ItemType, KeyType>::preorderTraverse(void visit(const ItemType &)) {
	preorder(visit, rootPtr);
}

/** inOrderTraverse
inOrder traverse from rootPtr
*/
template <class ItemType, typename KeyType>
void BinarySearchTree<ItemType, KeyType>::inOrderTraverse(void visit(const ItemType &)) {
	inOrder(visit, rootPtr);
}

/** postorderTraverse
postOrder traverse from rootPtr
*/
template <class ItemType, typename KeyType>
void BinarySearchTree<ItemType, KeyType>::postorderTraverse(void visit(const ItemType &)) {
	postorder(visit, rootPtr);
}

/** breadthFirstTraverse
breadthFirst traverse from rootPtr
*/
template <class ItemType, typename KeyType>
void BinarySearchTree<ItemType, KeyType>::breadthFirstTraverse(void visit(const ItemType &)) {
	breadthFirst(visit, rootPtr);
}

template <class ItemType, typename KeyType>
void BinarySearchTree<ItemType, KeyType>::printIndented(void visit(const ItemType &), BinaryNode<ItemType, KeyType>* pNode, int space) {
	if (pNode == nullptr) {
		return;
	}

	space += 3;
	printIndented(visit, pNode->getLeftChildPtr(), space);
	for (int i = 3; i < space; i++) {
		std::cout << " ";
	}
	visit(pNode->getData());
	printIndented(visit, pNode->getRightChildPtr(), space);
}


template <class ItemType, typename KeyType>
void BinarySearchTree<ItemType, KeyType>::printIndentedAll(void visit(const ItemType &)) {
	printIndented(visit, rootPtr, 0);
}

#endif

