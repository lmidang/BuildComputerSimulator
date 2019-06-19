#include "hashed_database_handler.h"

HashedDictionary<std::string, CompPart> HashedDataHandler::dict = HashedDictionary<std::string, CompPart>();
int HashedDataHandler::loadFactor = 0;
int HashedDataHandler::sumOfIndex = 0;
int HashedDataHandler::largest = 0;
std::ofstream HashedDataHandler::file;


void getNumNodes(const CompPart& cp) {
	HashedDataHandler::sumOfIndex++;
}

void writeHashFile(const CompPart &cp) {
	HashedDataHandler::file << cp.getPartType() << "," << cp.getName() << "," << cp.getPrice() << "," << cp.getManufacturer()
		<< "," << cp.getPower() << "," << cp.getPerformanceIndex() << "," << cp.getCompatibility() << "," << std::endl;
}

HashedDictionary<std::string, CompPart> & HashedDataHandler::getDict() {
	return dict;
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

void HashedDataHandler::add(const CompPart &item) {
	dict.add(normalize(item.getName()), item);
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