#pragma once
#include "BinarySearchTree.h"
#include "CompPart.h"


void printPart(CompPart&);
void addToList(CompPart&);

class BSTHandler
{
private:
	BinarySearchTree<CompPart> priceBST;
	BinarySearchTree<CompPart> performanceBST; 
public:
	static SinglyLinkedList<CompPart> list;
	static int typePart;

	BSTHandler();
	void add(CompPart&);
	bool remove(CompPart&);

	SinglyLinkedList<CompPart>& getListByPrice(int type);
	SinglyLinkedList<CompPart>& getListByPerformance(int type);
	void displayListByPrice();
	void displayListByPerformance();
	~BSTHandler();
};

