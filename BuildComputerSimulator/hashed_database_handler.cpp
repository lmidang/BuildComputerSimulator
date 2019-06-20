/*
Worked on by Lynn Dang
*/

#include "hashed_database_handler.h"

HashedDictionary<std::string, CompPartWrapper> HashedDataHandler::dict = HashedDictionary<std::string, CompPartWrapper>(31);
int HashedDataHandler::loadFactor = 0;
int HashedDataHandler::sumOfIndex = 0;
int HashedDataHandler::largest = 0;
std::ofstream HashedDataHandler::file;
Queue<CompPartWrapper> HashedDataHandler::thisList = Queue<CompPartWrapper>();


void getNumNodes(const CompPartWrapper& cp) {
	HashedDataHandler::sumOfIndex++;
}

void writeHashFile(const CompPartWrapper &cp) {
	if (cp.getPtr() == nullptr) {
		return;
	}
	HashedDataHandler::file << cp.get().getPartType() << "," << cp.get().getName() << "," << cp.get().getPrice() << "," << cp.get().getManufacturer()
		<< "," << cp.get().getPower() << "," << cp.get().getPerformanceIndex() << "," << cp.get().getCompatibility() << "," << std::endl;
}

HashedDictionary<std::string, CompPartWrapper> & HashedDataHandler::getDict() {
	return dict;
}

void freeCompPartList(const CompPartWrapper &cp){
	HashedDataHandler::thisList.enqueue(cp);
}

std::string HashedDataHandler::normalize(std::string name) {
	std::string norm = "";

	for (size_t i = 0; i < name.length(); i++) {
		if (name[i] != ' ') {
			if (name[i] >= 'a' && name[i] <= 'z')
				norm += name[i] - 32;
			else
				norm += name[i];
		}
	}

	return norm;
}

void HashedDataHandler::add(const CompPartWrapper &item) {
	dict.add(normalize(item.get().getName()), item);
}

void HashedDataHandler::calculateLoadFactor() {
	loadFactor = dict.getLoadFactor();
}

int HashedDataHandler::getLoadFactor() {
	return loadFactor;
}

int HashedDataHandler::getLongestList() {
	largest = 0;
	for (size_t i = 0; i < dict.getSize(); i++) {
		sumOfIndex = 0;
		dict.traverseIndex(getNumNodes, i);
		if (sumOfIndex > largest) {
			largest = sumOfIndex;
		}
	}

	return largest;
}

double HashedDataHandler::getAverageNodes() {
	return (double(dict.getNumberOfItems()) / dict.getSize());
}


void HashedDataHandler::writeHashToFile(std::string s) {
	file.open(s);
	file << "Part Type, Name, Price, Manufacturer, Power, Performance Index, Compatibility(or other)," << std::endl;
	dict.traverse(writeHashFile);
	file.close();
}

void HashedDataHandler::freeCompParts() {
	while (!thisList.isEmpty()) {
		thisList.front().freeComp();
		thisList.dequeue();
	}
}