#include "BSTHandler.h"

SinglyLinkedList<CompPartWrapper> BSTHandler::list;
int BSTHandler::typePart = 0;
double BSTHandler::budget = DBL_MAX;
std::ofstream BSTHandler::file = std::ofstream();

BSTHandler::BSTHandler()
{
	priceBST = new BinarySearchTree<CompPartWrapper, double>();
	performanceBST = new BinarySearchTree<CompPartWrapper, int>();
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

void printPart(const CompPartWrapper& cp) {
	std::cout << cp << std::endl;
}

void addToList(const CompPartWrapper& cp) {
	if (cp.get().getPartType() == BSTHandler::typePart && cp.get().getPrice() <= BSTHandler::budget)
		BSTHandler::list.insertAt(0, cp);
}

void writeToFile(const CompPartWrapper &cp) {
	BSTHandler::file << cp.get().getPartType() << "," << cp.get().getName() << "," << cp.get().getPrice() << "," << cp.get().getManufacturer()
		<< "," << cp.get().getPower()<< "," << cp.get().getPerformanceIndex() << "," << cp.get().getCompatibility() << "," << std::endl;
}

void BSTHandler::add(CompPartWrapper& cp) {
	priceBST->add(cp, cp.get().getPrice());
	performanceBST->add(cp, cp.get().getPerformanceIndex());
}

bool BSTHandler::remove(CompPartWrapper& cp) {
	bool gotem1;
	bool gotem2;
	gotem1 = priceBST->remove(cp, cp.get().getPrice());
	gotem2 = performanceBST->remove(cp, cp.get().getPerformanceIndex());

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

SinglyLinkedList<CompPartWrapper>& BSTHandler::getListByPrice(int type, double budget) {
	list.clear();
	typePart = type;
	this->budget = budget;
	priceBST->inOrderTraverse(addToList);
	list.reverse();
	return list;
}

SinglyLinkedList<CompPartWrapper>& BSTHandler::getListByPerformance(int type, double budget) {
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