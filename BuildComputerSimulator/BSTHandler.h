#pragma once
#include "BinarySearchTree.h"
#include "CompPart.h"


void printPart(CompPart&);
void addToList(CompPart&);
void writeToFile(CompPart&);

class BSTHandler
{
private:
	BinarySearchTree<CompPart> priceBST;
	BinarySearchTree<CompPart> performanceBST;

public:
	static SinglyLinkedList<CompPart> list;
	static int typePart;
	static std::ofstream file;

	BSTHandler();
	void add(CompPart&);
	bool remove(CompPart&);

	SinglyLinkedList<CompPart>& getListByPrice(int type);
	SinglyLinkedList<CompPart>& getListByPerformance(int type);
	void displayListByPrice();
	void displayListByPerformance();
	void updateFile(std::string s);
	~BSTHandler();
};

