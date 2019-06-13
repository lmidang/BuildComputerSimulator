#include <iostream>
#include "BSTHandler.h"
#include <fstream>

using namespace std;

int main()
{
	BSTHandler bstHandler;
	// Hastable

	std::string fileName = "input.csv"; // fix this later

	// reading input
	ifstream file;
	file.open(fileName);
	while (!file.eof()) {
		CompPart item;
		file >> item;
		//add to hash table

		bstHandler.add(item);
	}
	system("pause");
	return 0;
}