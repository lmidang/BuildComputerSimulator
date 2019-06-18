#include "ComputerBuilder.h"



ComputerBuilder::ComputerBuilder()
{
	SinglyLinkedList<CompPart> mList = SinglyLinkedList<CompPart>();
}

std::string ComputerBuilder::checkMissing() {
	std::string missingString = "nothing";
	for (int i = 0; i < 8; i++) {
		if (parts[0] == 0) {
			missingString = partsString[i];
			break;
		}
	}

	return missingString;
}
double ComputerBuilder::getPrice() {
	double total = 0;
	for (int i = 0; i < mList.getCount(); i++) {
		total += mList.getDataAt(i).getPrice();
	}
	return total;
}

int ComputerBuilder::getPower() {
	int total = 0;
	for (int i = 0; i < mList.getCount(); i++) {
		total += mList.getDataAt(i).getPower();
	}
	return total;
}

bool ComputerBuilder::add(CompPart &cp) {
	mList.insertAt(0, cp);
	parts[cp.getPartType()]++;
	return true;
}
bool ComputerBuilder::remove(int pos) {
	if (pos >= mList.getCount()) {
		return false;
	}
	else {
		parts[mList.getDataAt(pos).getPartType()]--;
		mList.deleteAt(pos);
		return true;
	}
}

ComputerBuilder::~ComputerBuilder()
{
	mList.clear();
}

void ComputerBuilder::listParts() {
	for (int i = 0; i < mList.getCount(); i++) {
		std::cout << mList.getDataAt(i) << std::endl;
	}
}