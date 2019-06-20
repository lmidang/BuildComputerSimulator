/*
Worked on by Lynn Dang
*/

#pragma once
#include "BinarySearchTree.h"
#include "CompPartWrapper.h"

// IO helper functions
void printPart(const CompPartWrapper&);
void addToList(const CompPartWrapper&);
void writeToFile(const CompPartWrapper&);

class BSTHandler
{
private:
	BinarySearchTree<CompPartWrapper, double> *priceBST;
	BinarySearchTree<CompPartWrapper, int> *performanceBST;

	// Efficiency counters
	int priceLoadFactor;
	int performanceLoadFactor;

public:
	static SinglyLinkedList<CompPartWrapper> list;
	static int typePart;
	static double budget;
	static std::ofstream file;
	
	// Constructor/destructor
	BSTHandler();
	~BSTHandler();

	// Mutators
	void add(CompPartWrapper&);
	bool remove(CompPartWrapper&);

	// For calculating efficiencies
	void calculateFactor();
	int getPriceLoadFactor();
	int getPerformanceLoadFactor();

	// for specific parts list
	SinglyLinkedList<CompPartWrapper>& getListByPrice(int type, double budget = DBL_MAX);
	SinglyLinkedList<CompPartWrapper>& getListByPerformance(int type, double budget = DBL_MAX);
	void displayListByPrice(int type);
	void displayListByPerformance(int type);
	void displayListByPriceIndented();
	void displayListByPerformanceIndented();

	void displayListByPrice();
	void displayListByPerformance();
	void updateFile(std::string s);
};

