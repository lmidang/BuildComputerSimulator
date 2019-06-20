#include "BSTHandler.h"

SinglyLinkedList<CompPart> BSTHandler::list;
int BSTHandler::typePart = 0;
double BSTHandler::budget = DBL_MAX;
std::ofstream BSTHandler::file = std::ofstream();

BSTHandler::BSTHandler()
{
	priceBST = new BinarySearchTree<CompPart, double>();
	performanceBST = new BinarySearchTree<CompPart, int>();
//	priceBST = BinarySearchTree<CompPart, double>();
//	performanceBST = BinarySearchTree<CompPart, int>();
}

BSTHandler::~BSTHandler() {
	if (priceBST != nullptr) {
		delete priceBST;
		priceBST = nullptr;
	}
	if (performanceBST != nullptr) {
		delete performanceBST;
		performanceBST = nullptr;
	}
}

void printPart(const CompPart& cp) {
	std::cout << cp << std::endl;
}

void addToList(const CompPart& cp) {
	if (cp.getPartType() == BSTHandler::typePart && cp.getPrice() <= BSTHandler::budget)
		BSTHandler::list.insertAt(0, cp);
}

void writeToFile(const CompPart &cp) {
	BSTHandler::file << cp.getPartType() << "," << cp.getName() << "," << cp.getPrice() << "," << cp.getManufacturer()
		<< "," << cp.getPower()<< "," << cp.getPerformanceIndex() << "," << cp.getCompatibility() << "," << std::endl;
}

void BSTHandler::add(CompPart& cp) {
	priceBST->add(cp, cp.getPrice());
	performanceBST->add(cp, cp.getPerformanceIndex());
}

bool BSTHandler::remove(CompPart& cp) {
	bool gotem1;
	bool gotem2;
	gotem1 = priceBST->remove(cp, cp.getPrice());
	gotem2 = performanceBST->remove(cp, cp.getPerformanceIndex());

	return (gotem1 && gotem2);
}


void BSTHandler::calculateFactor() {
	priceLoadFactor = priceBST->getLoadFactor();
	performanceLoadFactor = performanceBST->getLoadFactor();
}

int BSTHandler::getPriceLoadFactor() {
	return priceLoadFactor;
}

int BSTHandler::getPerformanceLoadFactor() {
	return performanceLoadFactor;
}

SinglyLinkedList<CompPart>& BSTHandler::getListByPrice(int type, double budget) {
	list.clear();
	typePart = type;
	this->budget = budget;
	priceBST->inOrderTraverse(addToList);
	list.reverse();
	return list;
}

SinglyLinkedList<CompPart>& BSTHandler::getListByPerformance(int type, double budget) {
	list.clear();
	typePart = type;
	this->budget = budget;
	performanceBST->inOrderTraverse(addToList);
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
	CompPart::printHeading(std::cout);
	priceBST->inOrderTraverse(printPart);
}

void BSTHandler::displayListByPerformance() {
	CompPart::printHeading(std::cout);
	performanceBST->inOrderTraverse(printPart);
}


void BSTHandler::displayListByPriceIndented() {
	priceBST->printIndentedAll(printPart);
}

void BSTHandler::displayListByPerformanceIndented() {
	performanceBST->printIndentedAll(printPart);
}

void BSTHandler::updateFile(std::string s) {
	file.open(s);
	file.open(s, std::ios::app);
	file <<"Part Type, Name, Price, Manufacturer, Power, Performance Index, Compatibility(or other)," << std::endl;
	priceBST->preorderTraverse(writeToFile);
	file.close();
}