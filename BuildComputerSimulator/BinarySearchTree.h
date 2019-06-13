#pragma once
/**
	This class is a Binary Search Tree class
*/

#ifndef _BINARY_SEARCH_TREE
#define _BINARY_SEARCH_TREE

#include <fstream>
#include "BinaryNode.h"
#include "queue.h"

template<class ItemType>
class BinarySearchTree
{
protected:
	BinaryNode<ItemType>* rootPtr;

	/** Returns height
	@pre tree is not empty
	@post height of the tree is calculated recursively
	@param BinaryNode ptr to check the height
	@return height of the node
	*/
	int getHeightHelper(BinaryNode<ItemType>*) const;
	/** Returns number of nodes
	@pre tree is not empty
	@post number of nodes in the subtree is calculated recursively
	@param BinaryNode ptr to the subtree get the number of nodes
	@return number of nodes of the subtree
	*/
	int getNumNodesHelper(BinaryNode<ItemType>*) const;

	/** Inserts node into the subtree
	@pre none
	@post node is inserted into subtree
	@param subtree root node ptr
	@param node to insert
	@return root node to subtree
	*/
	virtual BinaryNode<ItemType>* insertInOrder(BinaryNode<ItemType>*, BinaryNode<ItemType>*);

	/** Removes node by value
	@pre value exists in the tree
	@post value in the tree is removed
	@param subtree to removed from
	@param value to remove
	@param success boolean
	@return modified subtree root ptr
	*/
	virtual BinaryNode<ItemType>* removeValue(BinaryNode<ItemType>*, ItemType, bool&);

	/** Removes the node
	@pre node exists
	@post node is removed
	@param node to remove
	@return modified subtree root ptr
	*/
	BinaryNode<ItemType>* removeNode(BinaryNode<ItemType>*);

	/** Removes the leftmost node
	@pre node exists
	@post leftmost node is removed
	@param subtree to remove leftmost node
	@return modified subtree root ptr
	*/
	BinaryNode<ItemType>* removeLeftmostNode(BinaryNode<ItemType>*, ItemType&);

	/** Returns node by item
	@pre item exists
	@post node with item value is found
	@param subtree root ptr
	@param item
	@return node ptr with item value
	*/
	virtual BinaryNode<ItemType>* findNode(BinaryNode<ItemType>*, ItemType&) const;

	/** preorder traverse recursive
	@pre tree exists
	@post tree was traversed
	@param visit() function
	@param subtree root ptr
	*/
	void preorder(void visit(ItemType &), BinaryNode<ItemType>*);

	/** inorder traverse recursive
	@pre tree exists
	@post tree was traversed
	@param visit() function
	@param subtree root ptr
	*/
	void inOrder(void visit(ItemType &), BinaryNode<ItemType>*);

	/** postorder traverse recursive
	@pre tree exists
	@post tree was traversed
	@param visit() function
	@param subtree root ptr
	*/
	void postorder(void visit(ItemType &), BinaryNode<ItemType>*);

	/** breadthFirst traverse
	@pre tree exists
	@post tree was traversed
	@param visit() function
	@param subtree root ptr
	*/
	void breadthFirst(void visit(ItemType &), BinaryNode<ItemType>*);

public:
	class NotFoundException;

	BinarySearchTree();	// default constructor
	BinarySearchTree(const ItemType&);	// constructor with rootptr
	BinarySearchTree(const BinarySearchTree<ItemType>&);	// copy constructor
	virtual ~BinarySearchTree();	// destructor
	
	// accessors
	bool isEmpty() const;
	int getHeight() const;
	int getNumberOfNodes() const;
	ItemType& getRoot();
	
	/** adds to the tree
	@pre none
	@post item is added to the tree
	@param item was added
	@return success
	*/
	bool add(const ItemType&);

	/** removes item from the tree
	@pre item exists
	@post item is removed
	@param item to remove
	@return success
	*/
	bool remove(const ItemType&);

	// clears the tree
	void clear();

	/** checks whether item exists
	@pre none
	@post returns whether item exists
	@param item to check
	@return whether it exists
	*/
	bool contains(const ItemType&) const;

	/** preorder traverse
	@pre tree isn't emptry
	@post tree was traverse from the top
	@param visit
	*/
	void preorderTraverse(void visit(ItemType &));

	/** inOrder traverse
	@pre tree isn't emptry
	@post tree was traverse from the top
	@param visit
	*/
	void inOrderTraverse(void visit(ItemType &));

	/** postorder traverse
	@pre tree isn't emptry
	@post tree was traverse from the top
	@param visit
	*/
	void postorderTraverse(void visit(ItemType &));

	/** breadth first traverse
	@pre tree isn't emptry
	@post tree was traverse from the top
	@param visit
	*/
	void breadthFirstTraverse(void visit(ItemType &));
};

#include "BinarySearchTree.cpp"
#endif

