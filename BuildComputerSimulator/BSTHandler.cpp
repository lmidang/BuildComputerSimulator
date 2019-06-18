#include "BSTHandler.h"

SinglyLinkedList<CompPart> BSTHandler::list;
int BSTHandler::typePart = 0;
double BSTHandler::budget = DBL_MAX;
std::ofstream BSTHandler::file = std::ofstream();

BSTHandler::BSTHandler()
{
	priceBST = BinarySearchTree<CompPart>();
	performanceBST = BinarySearchTree<CompPart>();
}

BSTHandler::~BSTHandler() {}

void printPart(CompPart& cp) {	// fix if we want
	std::cout << cp << std::endl;
}

void addToList(CompPart& cp) {
	if (cp.getPartType() == BSTHandler::typePart && cp.getPrice() <= BSTHandler::budget)
		BSTHandler::list.insertAt(0, cp);
}

void writeToFile(CompPart &cp) {
	BSTHandler::file << cp.getPartType() << "," << cp.getName() << "," << cp.getPrice()
		<< "," << cp.getManufacturer() << "," << cp.getPower() << "," << cp.getPerformanceIndex()
		<< "," << cp.getCompatibility() << "," << std::endl;
}

void BSTHandler::add(CompPart& cp) {
	cp.setSortType(CompPart::kByPrice);
	priceBST.add(cp);

	CompPart item = CompPart(cp);
	item.setSortType(CompPart::kByPerformanceIndex);
	performanceBST.add(item);
}

bool BSTHandler::remove(CompPart& cp) {
	bool gotem1;
	bool gotem2;
	CompPart item = CompPart(cp);
	item.setSortType(CompPart::kByPrice);
	gotem1 = priceBST.remove(item);

	item = CompPart(cp);
	item.setSortType(CompPart::kByPerformanceIndex);
	gotem2 = performanceBST.remove(item);

	return (gotem1 && gotem2);
}

SinglyLinkedList<CompPart>& BSTHandler::getListByPrice(int type, double budget) {
	list.clear();
	typePart = type;
	this->budget = budget;
	priceBST.inOrderTraverse(addToList);
	list.reverse();
	return list;
}

SinglyLinkedList<CompPart>& BSTHandler::getListByPerformance(int type) {
	list.clear();
	typePart = type;
	performanceBST.inOrderTraverse(addToList);
	list.reverse();
	return list;
}

void BSTHandler::displayListByPrice(int type) {
	getListByPrice(type);

	for (size_t i = 0; i < list.getCount(); i++) {
		std::cout << list.getDataAt(i) << std::endl;
	}
}

void BSTHandler::displayListByPerformance(int type) {
	getListByPerformance(type);

	for (size_t i = 0; i < list.getCount(); i++) {
		std::cout << list.getDataAt(i) << std::endl;
	}
}

void BSTHandler::displayListByPrice() {
	priceBST.inOrderTraverse(printPart);
}

void BSTHandler::displayListByPerformance() {
	performanceBST.inOrderTraverse(printPart);
}

void BSTHandler::updateFile(std::string s) {
	file.open(s);
	priceBST.preorderTraverse(writeToFile);
	file.close();
}