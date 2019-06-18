#include <iostream>
#include <fstream>
#include "input_tools.h"
#include "BSTHandler.h"
#include "hashed_dict_handler.h"

using namespace std;

void readFromFile(BSTHandler &);

int main()
{
	BSTHandler bstHandler, shoppingCartHandler;
	readFromFile(bstHandler);

	double budget;

	cout << "Please enter your budget:\n";
	budget = inputNumber(0, DBL_MAX, "$");

	bool exit = false;

	do {
		cout << "Please select what type of computer part you would like to purchase:\n";
		CompPart::partTypes partType = static_cast<CompPart::partTypes>(menu(CompPart::partNames, CompPart::NUM_PARTS));
		cout << endl;

		SinglyLinkedList<CompPart> priceList = bstHandler.getListByPrice(partType, budget);

		if (priceList.isEmpty())
			cout << "You are too poor to afford anything!\n\n";
		else {
			CompPart::printHeading(cout);
			cout << priceList << endl;
		}

		priceList.traverse(HashedDictHandler::add);

		bool valid = false;

		do {
			cout << "Please input the name of the computer part you would like to purchase, or enter nothing to go back:\n";

			try {
				string input = inputString(true);

				if (input != "") {
					CompPart part = HashedDictHandler::getDict().getItem(HashedDictHandler::normalize(input));
					cout << "You just bought:\n";
					cout << part << "\n\n";

					shoppingCartHandler.add(part);
					budget -= part.getPrice();

					cout << "Your current shopping cart contains:\n";
					shoppingCartHandler.displayListByPrice();
					cout << endl;

					cout << "You have $" << setprecision(2) << fixed << budget << " remaining.\n\n";
				}

				valid = true;
			}
			catch (const char *msg) {
				cerr << msg << "\n\n";
			}
		} while (!valid);
	} while (!exit);

	system("pause");
	return 0;
}

void readFromFile(BSTHandler &bstHandler) {
	ifstream inFile;
	const string DEFAULT_FILE_NAME = "data.csv";
	string fileName;
	bool valid = false;

	// Open database file
	do {
		cout << "Please input the file name for the database, or press ENTER to default to: " << DEFAULT_FILE_NAME << endl;
		fileName = inputString(true);

		if (fileName == "")
			fileName = DEFAULT_FILE_NAME;

		inFile.open(fileName);

		if (inFile)
			valid = true;
		else
			cerr << "Cannot find file!\n\n";
	} while (!valid);


	// Read data from file
	string temp;
	getline(inFile, temp);

	while (!inFile.eof()) {
		CompPart item;
		inFile >> item;

		bstHandler.add(item);
	}
}