#pragma once
#include "BinarySearchTree.h"
#include "CompPart.h"

class BSTHandler
{
private:
	BinarySearchTree<CompPart> priceBST;
	BinarySearchTree<CompPart> performanceBST;

	SinglyLinkedList<CompPart> list;
	int partType;

	void printPart(CompPart&);
	void addToList(CompPart&);
public:
	BSTHandler();
	void add(CompPart&);
	bool remove(CompPart&);

	SinglyLinkedList<CompPart>& getListByPrice(int type);
	SinglyLinkedList<CompPart>& getListByPerformance(int type);
	void displayListByPrice();
	void displayListByPerformance();
	~BSTHandler();
};

