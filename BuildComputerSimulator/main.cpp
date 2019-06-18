#include <iostream>
#include <fstream>
#include "input_tools.h"
#include "BSTHandler.h"
#include "hashed_dict_handler.h"
#include "hashed_database_handler.h"

using namespace std;

void readFromFile(BSTHandler &);
void printItem(CompPart const &);

int main()
{
	const string DEFAULT_FILE_NAME = "data.csv";
	BSTHandler bstHandler;
	BSTHandler shoppingCartHandler;
	readFromFile(bstHandler);

	bool isCompletelyDone = false;
	do {
		string mainOption[] = {"Edit Database", "Build a Computer", "Exit"};
		size_t userOption = menu(mainOption, 3);
		
		switch (userOption) {
		case 0: {
			bool isEditingDatDone = false;
			do {
				string editingOptions[] = { "Add Data", "Remove Data", "Search by name", "List in hash sequence", "List in key sequence", "List by Price", "List by Performance", "Efficiency", "Exit" };
				size_t editingChoice = menu(editingOptions, 9);

				switch(editingChoice) {
				case 0: { // add
					string stringInput;
					int intInput;
					double doubleInput;

					CompPart newCompPart;
					cout << "Select the part type from the menu:" << endl;
					intInput = menu(CompPart::partNames, CompPart::NUM_PARTS);
					newCompPart.setPartType(intInput);
					cout << "Enter a name: ";
					stringInput = inputString();
					newCompPart.setName(stringInput);
					cout << "Enter a price: ";
					doubleInput = inputNumber();
					newCompPart.setPrice(doubleInput);
					cout << "Enter the manufacturer: ";
					stringInput = inputString();
					newCompPart.setManufacturer(stringInput);
					cout << "Enter the power: ";
					intInput = int(inputNumber());
					newCompPart.setPower(intInput);
					cout << "Enter the performanceIndex: ";
					intInput = int(inputNumber());
					newCompPart.setPerformanceIndex(intInput);
					if ((newCompPart.getPartType() == CompPart::kCPU) || (newCompPart.getPartType() == CompPart::kMotherBoard)) {
						cout << "Enter compatibility: ";
						stringInput = inputString();
						newCompPart.setCompatibility(stringInput);
					}

					bstHandler.add(newCompPart);
					HashedDataHandler::add(newCompPart);
					break;
				}
				case 1: { // remove by name
					cout << "Enter the name of the part: " << endl;
					string userInput;
					userInput = inputString();
					try {
						CompPart toDelete = HashedDataHandler::getDict().getItem(HashedDataHandler::normalize(userInput));
						toDelete.setSortType(CompPart::kByPrice);
						bstHandler.remove(toDelete);
						HashedDataHandler::getDict().remove(userInput);
						cout << "Item removed.\n\n";
					} catch (...) {
						cout << "Item was not in database\n\n";
					}
					break;
				}
				case 2: { // search
					cout << "Enter the name of the part: " << endl;
					string input;
					input = inputString();

					try {
						CompPart part = HashedDataHandler::getDict().getItem(HashedDataHandler::normalize(input));
						cout << part << endl << endl;

					} catch (...) {
						cout << "Item not found.\n";
					}
					break;
				}
				case 3: { // list hashed sequence
					HashedDataHandler::getDict().traverse(printItem);
					break;
				}
				case 4: { // list key sequence (FIX THIS LATER)
					HashedDataHandler::getDict().traverse(printItem);
					break;
				}
				case 5: { // list price
					bstHandler.displayListByPrice();
					break;
				}
				case 6: { // list performance
					bstHandler.displayListByPerformance();
					break;
				}
				case 7: { // efficiency DO THIS LATER
					cout << "efficiency :P\n";
					break;
				}
				case 8: { // exit
					string fileName;
					isEditingDatDone = true;
					cout << "Please input the file name to save the database, press ENTER to default : " << DEFAULT_FILE_NAME << ", or enter 0 to exit without saving." << endl;
					fileName = inputString(true);

					if (fileName == "0") {
						break;
					}
					if (fileName == "")
						fileName = DEFAULT_FILE_NAME;
					bstHandler.updateFile(fileName);
				}
				default:
					cout << "Invalid input.\n\n";
				}
			} while (!isEditingDatDone);
			break;
		}
		case 1: {	// build computer option here
			break;
		}
		case 2: { // exit
			isCompletelyDone = true;
			break;
		}
		default: {
			cout << "Invalid input.\n";
		}
		}

	} while (!isCompletelyDone);
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
		try {
			CompPart item;
			inFile >> item;

			HashedDataHandler::add(item);
			bstHandler.add(item);
		}
		catch (CompPart::ExtraSpaceException) {

		}
	}
}

void printItem(CompPart const &cp) {
	cout << cp << endl;
}