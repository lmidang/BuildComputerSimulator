#include "BinarySearchTree.h"

// default constructor initializes rootptr to nullptr
template <class ItemType>
BinarySearchTree<ItemType>::BinarySearchTree()
{
	rootPtr = nullptr;
}

// constructor initializing rootptr with rootItem
template <class ItemType>
BinarySearchTree<ItemType>::BinarySearchTree(const ItemType& rootItem)
{
	rootPtr = new BinaryNode<ItemType>(rootItem);
}

// copy constructor
template <class ItemType>
BinarySearchTree<ItemType>::BinarySearchTree(const BinarySearchTree<ItemType> &bst)
{
	rootPtr = new BinaryNode<ItemType>(bst.rootPtr->getData());
}

// destructor
template <class ItemType>
BinarySearchTree<ItemType>::~BinarySearchTree()
{
	if (!isEmpty()) {
		clear();
	}
}

// returns whether rootptr is nullptr
template <class ItemType>
bool BinarySearchTree<ItemType>::isEmpty() const
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
template <class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::insertInOrder(BinaryNode<ItemType>* subTreePtr, BinaryNode<ItemType>* newNodePtr)
{
	if (subTreePtr == nullptr) {
		return newNodePtr;
	}
	else if (subTreePtr->getData() > newNodePtr->getData())
	{
		BinaryNode<ItemType>* tempPtr = insertInOrder(subTreePtr->getLeftChildPtr(), newNodePtr);
		loadFactor++;

		subTreePtr->setLeftChildPtr(tempPtr);
		loadFactor++;
	}
	else {
		BinaryNode<ItemType>* tempPtr = insertInOrder(subTreePtr->getRightChildPtr(), newNodePtr);
		loadFactor++;

		subTreePtr->setRightChildPtr(tempPtr);
		loadFactor++;
	}
	return subTreePtr;
}

/** add
adds newNodePtr from newData to root tree using insertInOrder
*/
template <class ItemType>
bool BinarySearchTree<ItemType>::add(const ItemType& newData) {
	BinaryNode<ItemType>* newNodePtr = new BinaryNode<ItemType>(newData);
	loadFactor++;

	rootPtr = insertInOrder(rootPtr, newNodePtr);
	loadFactor++;
	return true;
}

// Removes a target value from a binary search tree recursively
template <typename ItemType>
BinaryNode<ItemType> * BinarySearchTree<ItemType>::removeValue(BinaryNode<ItemType> *pSubTree, const ItemType target, bool &success) {
	if (pSubTree == nullptr) {
		success = false;
		return nullptr;
	}
	else if (pSubTree->getData() == target) {
		pSubTree = removeNode(pSubTree);
		success = true;
		return pSubTree;
	}
	else if (pSubTree->getData() > target) {
		BinaryNode<ItemType> *tempPtr = removeValue(pSubTree->getLeftChildPtr(), target, success);
		pSubTree->setLeftChildPtr(tempPtr);
		return pSubTree;

	}
	else {
		BinaryNode<ItemType> *tempPtr = removeValue(pSubTree->getRightChildPtr(), target, success);
		pSubTree->setRightChildPtr(tempPtr);
		return pSubTree;
	}
}

//removes a node from the binary search tree
//checks if node has child nodes
//if does not, delete node
template <typename ItemType>
BinaryNode<ItemType> * BinarySearchTree<ItemType>::removeNode(BinaryNode<ItemType> *pNode) {
	bool hasLeftChild = pNode->getLeftChildPtr() != nullptr,
		hasRightChild = pNode->getRightChildPtr() != nullptr;

	if (!hasLeftChild && !hasRightChild) {
		delete pNode;
		pNode = nullptr;
		return pNode;
	}

	if (hasLeftChild != hasRightChild) {
		BinaryNode<ItemType> *pChild;

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
		BinaryNode<ItemType> *tempPtr = removeLeftmostNode(pNode->getRightChildPtr(), newNodeData);
		pNode->setRightChildPtr(tempPtr);
		pNode->setData(newNodeData);
		return pNode;
	}

}

// removes leftmost
template <typename ItemType>
BinaryNode<ItemType> * BinarySearchTree<ItemType>::removeLeftmostNode(BinaryNode<ItemType> *pSubTree, ItemType &inorderSuccessor) {
	if (pSubTree->getLeftChildPtr() == nullptr) {
		inorderSuccessor = pSubTree->getData();
		return removeNode(pSubTree);
	}

	pSubTree->setLeftChildPtr(removeLeftmostNode(pSubTree->getLeftChildPtr(), inorderSuccessor));
	return pSubTree;
}

/** remove
1 removes item by removeValue(rootPtr, item, success)
2 return success
*/
template <class ItemType>
bool BinarySearchTree<ItemType>::remove(const ItemType& item) {
	bool success = false;
	rootPtr = removeValue(rootPtr, item, success);
	return success;
}

/** finds the node with item value
1 if subTreePtr is null, return nullptr
2 else if subTreePtr data is item, return subTreePtr
3 else if subTreePtr data is greater than item, return findNode(subTreePtr left child)
4 else return findNode(subTreePtr right child)
*/
template <class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::findNode(BinaryNode<ItemType>* subTreePtr, ItemType &item) const
{
	if (subTreePtr == nullptr) {
		return nullptr;
	}
	else if (subTreePtr->getData() == item) {
		return subTreePtr;
	}
	else if (subTreePtr->getData() > item) {
		return findNode(subTreePtr->getLeftChildPtr(), item);
	}
	else {
		return findNode(subTreePtr->getRightChildPtr(), item);
	}
}

/** clear
1 while rootPtr is not null, remove rootPtr
*/
template <class ItemType>
void BinarySearchTree<ItemType>::clear()
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
template <class ItemType>
int BinarySearchTree<ItemType>::getHeightHelper(BinaryNode<ItemType>* subTreePtr) const
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
template <class ItemType>
int BinarySearchTree<ItemType>::getHeight() const {
	return getHeightHelper(rootPtr);
}

/** getNumNodesHelper
1 if subTreePtr is nullptr return 0
2 else
	1 getNumNodesHelper(subTreePtr leftChild)
	2 getNumNodesHelper(subTreePtr rightChild)
	3 return left + right + 1
*/
template <class ItemType>
int BinarySearchTree<ItemType>::getNumNodesHelper(BinaryNode<ItemType>* subTreePtr) const
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
template <class ItemType>
int BinarySearchTree<ItemType>::getNumberOfNodes() const {
	return getNumNodesHelper(rootPtr);
}

template <class ItemType>
ItemType& BinarySearchTree<ItemType>::getRoot() {
	return rootPtr->getData();
}

template <class ItemType>
int BinarySearchTree<ItemType>::getLoadFactor() {
	return loadFactor;
}

/** contains
returns whether node of item exists
*/
template <class ItemType>
bool BinarySearchTree<ItemType>::contains(const ItemType &anEntry) const {
	return (findNode(rootPtr, anEntry) != nullptr);
}

/** preorder
1 is treePtr is null
	1 process node
	2 preorder(left)
	3 preorder(right)
*/
template <class ItemType>
void BinarySearchTree<ItemType>::preorder(void visit(const ItemType &), BinaryNode<ItemType>* treePtr)
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
template <class ItemType>
void BinarySearchTree<ItemType>::inOrder(void visit(const ItemType &), BinaryNode<ItemType>* treePtr)
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
template <class ItemType>
void BinarySearchTree<ItemType>::postorder(void visit(const ItemType &), BinaryNode<ItemType>* treePtr)
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
template <class ItemType>
void BinarySearchTree<ItemType>::breadthFirst(void visit(const ItemType &), BinaryNode<ItemType>* treePtr)
{
	if (treePtr != nullptr) {
		BinaryNode<ItemType> *currentNode = rootPtr;
		Queue<BinaryNode<ItemType>*> bfQueue;
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
template <class ItemType>
void BinarySearchTree<ItemType>::preorderTraverse(void visit(const ItemType &)) {
	preorder(visit, rootPtr);
}

/** inOrderTraverse
inOrder traverse from rootPtr
*/
template <class ItemType>
void BinarySearchTree<ItemType>::inOrderTraverse(void visit(const ItemType &)) {
	inOrder(visit, rootPtr);
}

/** postorderTraverse
postOrder traverse from rootPtr
*/
template <class ItemType>
void BinarySearchTree<ItemType>::postorderTraverse(void visit(const ItemType &)) {
	postorder(visit, rootPtr);
}

/** breadthFirstTraverse
breadthFirst traverse from rootPtr
*/
template <class ItemType>
void BinarySearchTree<ItemType>::breadthFirstTraverse(void visit(const ItemType &)) {
	breadthFirst(visit, rootPtr);
}

template <class ItemType>
void BinarySearchTree<ItemType>::printIndented(void visit(const ItemType &), BinaryNode<ItemType>* pNode, int space) {
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


template <class ItemType>
void BinarySearchTree<ItemType>::printIndentedAll(void visit(const ItemType &)) {
	printIndented(visit, rootPtr, 0);
}
