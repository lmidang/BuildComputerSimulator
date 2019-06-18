#include <iostream>
#include "BSTHandler.h"
#include <fstream>

using namespace std;

int main()
{
	BSTHandler bstHandler;
	// Hastable

	std::string fileName = "data.csv"; // fix this later

	// reading input
	ifstream file;
	file.open(fileName);
	if (!file) {
		cout << "Cannot find file.\n";
		system("pause");
		return 0;
	}
	std::string random;
	getline(file, random);
	while (!file.eof()) {
		CompPart item;
		//file >> item;
		cout << item << endl;
		//add to hash table

		bstHandler.add(item);
		bstHandler.displayListByPrice();
	}
	system("pause");
	return 0;
}