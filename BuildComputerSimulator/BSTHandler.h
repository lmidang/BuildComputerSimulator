/*
Worked on by Lynn Dang
*/

#pragma once
#include "BinarySearchTree.h"
#include "CompPart.h"

// IO helper functions
void printPart(const CompPart&);
void printPartIndented(const CompPart&);
void addToList(const CompPart&);
void writeToFile(const CompPart&);

class BSTHandler
{
private:
	// The binary search trees
	BinarySearchTree<CompPart, double> *priceBST;
	BinarySearchTree<CompPart, int> *performanceBST;

	// Efficiency counters
	int priceLoadFactor;
	int performanceLoadFactor;

public:
	static SinglyLinkedList<CompPart> list;
	static int typePart;
	static double budget;
	static std::ofstream file;
	
	// Constructor/destructor
	BSTHandler();
	~BSTHandler();

	// Mutators
	void add(CompPart&);
	bool remove(CompPart&);

	// For calculating efficiencies
	void calculateFactor();
	int getPriceLoadFactor();
	int getPerformanceLoadFactor();

	// for specific parts list
	SinglyLinkedList<CompPart>& getListByPrice(int type, double budget = DBL_MAX);
	SinglyLinkedList<CompPart>& getListByPerformance(int type, double budget = DBL_MAX);
	void displayListByPrice(int type);
	void displayListByPerformance(int type);
	void displayListByPriceIndented();
	void displayListByPerformanceIndented();

	void displayListByPrice();
	void displayListByPerformance();
	void updateFile(std::string s);
};

