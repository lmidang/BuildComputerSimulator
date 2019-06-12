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
		subTreePtr->setLeftChildPtr(tempPtr);
	}
	else {
		BinaryNode<ItemType>* tempPtr = insertInOrder(subTreePtr->getRightChildPtr(), newNodePtr);
		subTreePtr->setRightChildPtr(tempPtr);
	}
	return subTreePtr;
}

/** add
adds newNodePtr from newData to root tree using insertInOrder
*/
template <class ItemType>
bool BinarySearchTree<ItemType>::add(const ItemType& newData) {
	BinaryNode<ItemType>* newNodePtr = new BinaryNode<ItemType>(newData);
	rootPtr = insertInOrder(rootPtr, newNodePtr);
	return true;
}

/** removeValue
1 if subTreePtr is nullptr
	1 removal not successful
2 else if subTreePtr data is item
	1 removeNode(subTreePtr)
	2 return subTreePtr
3 else if subTree data is greater than item
	1 removeValue from left child subtree
	2 return subTreePtr
4 else 
	1 removeValue from right child subtree
	2 return subtreePtr
*/
template <class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::removeValue(BinaryNode<ItemType>* subTreePtr, ItemType item, bool &success)
{	
	if (subTreePtr == nullptr) {
		success = false;
		return nullptr;
	}
	else if (subTreePtr->getData() == item) {
		subTreePtr = removeNode(subTreePtr);
		success = true;
		return subTreePtr;
	}
	else if (subTreePtr->getData() > item) {
		BinaryNode<ItemType>* tempPtr = removeValue(subTreePtr->getLeftChildPtr(), item, success);
		subTreePtr->setLeftChildPtr(tempPtr);
		return subTreePtr;
	}
	else {
		BinaryNode<ItemType>* tempPtr = removeValue(subTreePtr->getRightChildPtr(), item, success);
		subTreePtr->setRightChildPtr(tempPtr);
		return subTreePtr;
	}
}

/** removes node
1 if nodePtr is leaf
	1 delete node
	2 return nodePtr
2 else if nodeptr has one child
	1 if leftChildPtr exists
		1 connect nodePtr leftChild
	2 else
		1 connect nodePtr rigthChild
	3 delete nodePtr
	4 return nodeToConnectPtr
3 else 
	1 set nodePtr right child to removeLeftmostNode(nodePtr right childe, newNodeValue)
	2 set nodePtr setData to newNodeValue
	3 return nodePtr
*/
template <class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::removeNode(BinaryNode<ItemType>* nodePtr) {
	if (nodePtr->isLeaf()) {
		delete nodePtr;
		nodePtr = nullptr;
		return nodePtr;
	}
	else if (nodePtr->getNumChildren() == 1) {
		BinaryNode<ItemType> *nodeToConnectPtr;
		if (nodePtr->getLeftChildPtr() != nullptr) {
			nodeToConnectPtr = nodePtr->getLeftChildPtr();
		}
		else
			nodeToConnectPtr = nodePtr->getRightChildPtr();
		delete nodePtr;
		nodePtr = nullptr;
		return nodeToConnectPtr;
	}
	else {
		ItemType newNodeValue;
		BinaryNode<ItemType> *tempPtr = removeLeftmostNode(nodePtr->getRightChildPtr(), newNodeValue);
		nodePtr->setRightChildPtr(tempPtr);
		nodePtr->setData(newNodeValue);
		return nodePtr;
	}
}

/** removeLeftmostNode
if nodePtr has no left child, set inorderSuccessor to nodePtrData and return removeNode(nodePtr)
else return removeLeftMostNode(nodePtr left child, inorderSuccessor)
*/
template <class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::removeLeftmostNode(BinaryNode<ItemType>* nodePtr, ItemType &inorderSuccessor)
{
	if (nodePtr->getLeftChildPtr() == nullptr) {
		inorderSuccessor = nodePtr->getData();
		return removeNode(nodePtr);
	}
	else {
		return removeLeftmostNode(nodePtr->getLeftChildPtr(), inorderSuccessor);
	}
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
void BinarySearchTree<ItemType>::preorder(void visit(ItemType &), BinaryNode<ItemType>* treePtr)
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
void BinarySearchTree<ItemType>::inOrder(void visit(ItemType &), BinaryNode<ItemType>* treePtr)
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
void BinarySearchTree<ItemType>::postorder(void visit(ItemType &), BinaryNode<ItemType>* treePtr)
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
void BinarySearchTree<ItemType>::breadthFirst(void visit(ItemType &), BinaryNode<ItemType>* treePtr)
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
void BinarySearchTree<ItemType>::preorderTraverse(void visit(ItemType &)) {
	preorder(visit, rootPtr);
}

/** inOrderTraverse
inOrder traverse from rootPtr
*/
template <class ItemType>
void BinarySearchTree<ItemType>::inOrderTraverse(void visit(ItemType &)) {
	inOrder(visit, rootPtr);
}

/** postorderTraverse
postOrder traverse from rootPtr
*/
template <class ItemType>
void BinarySearchTree<ItemType>::postorderTraverse(void visit(ItemType &)) {
	postorder(visit, rootPtr);
}

/** breadthFirstTraverse
breadthFirst traverse from rootPtr
*/
template <class ItemType>
void BinarySearchTree<ItemType>::breadthFirstTraverse(void visit(ItemType &)) {
	breadthFirst(visit, rootPtr);
}

template<class ItemType>
bool BinarySearchTree<ItemType>::fillUpFile(std::ifstream& f) {
	while (!f.eof()) {
		ItemType item;
		f >> item;
		add(item);
	}
}
