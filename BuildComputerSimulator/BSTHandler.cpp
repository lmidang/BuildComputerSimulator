#include "BSTHandler.h"



BSTHandler::BSTHandler()
{
	priceBST = BinarySearchTree<CompPart>();
	performanceBST = BinarySearchTree<CompPart>();

	list = SinglyLinkedList<CompPart>();
	partType = 0;
}

BSTHandler::~BSTHandler() {}

void BSTHandler::printPart(CompPart& cp) {	// fix if we want
	std::cout << cp << std::endl;
}

void BSTHandler::addToList(CompPart& cp) {
	if (cp.getPartType == partType) {
		list.insertAt(list.getCount(), cp);
	}
}

void BSTHandler::add(CompPart& cp) {
	priceBST.add(cp);

	CompPart item = CompPart(cp);
	item.setSortType(CompPart::kByPerformanceIndex);
	performanceBST.add(cp);
}

bool BSTHandler::remove(CompPart& cp) {
	bool gotem1;
	bool gotem2;
	cp.setSortType(CompPart::kByPrice);
	gotem1 = priceBST.remove(cp);

	cp.setSortType(CompPart::kByPerformanceIndex);
	gotem2 = performanceBST.remove(cp);

	return (gotem1 && gotem2);
}

SinglyLinkedList<CompPart>& BSTHandler::getListByPrice(int type) {
	partType = type;
	priceBST.inOrderTraverse(this->addToList);
	return list;
}

SinglyLinkedList<CompPart>& BSTHandler::getListByPerformance(int type) {
	partType = type;
	performanceBST.inOrderTraverse(this->addToList);
	return list;
}

void BSTHandler::displayListByPrice() {
	priceBST.inOrderTraverse(this->printPart);
}

void BSTHandler::displayListByPerformance() {
	performanceBST.inOrderTraverse(this->printPart);
}