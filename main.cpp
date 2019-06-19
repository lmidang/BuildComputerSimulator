#include <iostream>
#include <fstream>
#include "input_tools.h"
#include "BSTHandler.h"
#include "hashed_dict_handler.h"
#include "hashed_database_handler.h"

using namespace std;

void readFromFile(BSTHandler &);
void printItem(CompPart const &);
void addPartToCart(BSTHandler &, BinarySearchTree<CompPart> &, double &);
void removePartFromCart(BinarySearchTree<CompPart> &, double &);
void changeBudget(double &);
void viewCart(BinarySearchTree<CompPart> &);
void saveCart(BinarySearchTree<CompPart> &);

int main()
{
	const string DEFAULT_FILE_NAME = "data.csv";
	BSTHandler bstHandler;
	BinarySearchTree<CompPart> shoppingCart;
	readFromFile(bstHandler);

	bool isCompletelyDone = false;

	string mainOption[] = {"Edit Database", "Build a Computer", "Exit"};
	string menuOptions[] = {
		"Add computer part to shopping cart",
		"Remove computer part from shopping cart",
		"View shopping cart",
		"Change budget",
		"Exit"
	};

	do {
		size_t userOption = menu(mainOption, 3);
		
		switch (userOption) {
		case 0: {
			bool isEditingDatDone = false;
			do {
				string editingOptions[] = { "Add Data", "Remove Data", "Search by name", "List in hash sequence", "List in key sequence", "List by Price", "List by Performance", "Exit" };
				size_t editingChoice = menu(editingOptions, 8);

				switch(editingChoice) {
				case 0: { // add
					string stringInput;
					int intInput;
					double doubleInput;

					CompPart newCompPart;
					cout << "\nSelect the part type from the menu:" << endl;
					intInput = menu(CompPart::partNames, CompPart::NUM_PARTS);
					newCompPart.setPartType(intInput);
					cout << "Enter a name: ";
					stringInput = inputString();

					try{
						CompPart part = HashedDataHandler::getDict().getItem(HashedDataHandler::normalize(stringInput));
						cout << "Part already exists.\n";
						break;
					}
					catch (...) {}

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
					cout << "Enter an index: " << endl;
					int input = int(inputNumber());

					try {
						HashedDataHandler::getDict().traverseIndex(printItem, input);
					}
					catch (HashedDictionary<string, CompPart>::OutOfRangeException()) {
						cout << "Index not in range\n";
					}
					break;
				}
				case 5: { // list price
					string displayType[] = { "By Price", "Indented" };
					size_t displayChoice = menu(displayType, 2);

					switch (displayChoice) {
					case 0:
						bstHandler.displayListByPrice();
						break;
					case 1:
						bstHandler.displayListByPriceIndented();
						break;
					default:
						cout << "invalid input\n" << endl;
						break;
					}
					break;
				}
				case 6: { // list performance
					string displayType[] = { "By Price", "Indented" };
					size_t displayChoice = menu(displayType, 2);

					switch (displayChoice) {
					case 0:
						bstHandler.displayListByPerformance();
						break;
					case 1:
						bstHandler.displayListByPerformanceIndented();
						break;
					default:
						cout << "invalid input\n" << endl;
						break;
					}
					break;
				}
				case 7: { // exit
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
			double budget;
			changeBudget(budget);

			bool exit = false;

			do {
				size_t menuChoice = menu(menuOptions, 5);
				cout << endl;

				switch (menuChoice) {
				case 0:
					addPartToCart(bstHandler, shoppingCart, budget);
					break;
				case 1:
					removePartFromCart(shoppingCart, budget);
					break;
				case 2:
					viewCart(shoppingCart);
					break;
				case 3:
					changeBudget(budget);
					break;
				case 4:
					saveCart(shoppingCart);
					exit = true;
					break;
				}

				cout << "You have $" << setprecision(2) << fixed << budget << " remaining.\n\n";
			} while (!exit);
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
	static const string DEFAULT_FILE_NAME = "data.csv";
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
	inFile.close();
}

void printItem(CompPart const &cp) {
	cout << cp << endl;
}

void addPartToCart(BSTHandler &bstHandler, BinarySearchTree<CompPart> &shoppingCart, double &budget) {
	cout << "Please select what type of computer part you would like to purchase:\n";
	CompPart::partTypes partType = static_cast<CompPart::partTypes>(menu(CompPart::partNames, CompPart::NUM_PARTS));
	cout << endl;

	string sortOptions[] = { "Price", "Performance" };
	cout << "How would you like to sort the parts?\n";
	size_t sortChoice = menu(sortOptions, 2);
	cout << endl;

	SinglyLinkedList<CompPart> partsList;

	switch (sortChoice) {
	case 0:
		partsList = bstHandler.getListByPrice(partType, budget);
		break;
	case 1:
		partsList = bstHandler.getListByPerformance(partType, budget);
		break;
	}

	if (partsList.isEmpty())
		cout << "You are too poor to afford anything! Consider getting a job.\n\n";
	else {
		CompPart::printHeading(cout);
		cout << partsList << endl;
	}

	HashedDictHandler::getDict().clear();
	partsList.traverse(HashedDictHandler::add);

	bool valid = false;

	do {
		cout << "Please input the name of the computer part you would like to purchase, or enter nothing to go back:\n";
		string input = inputString(true);

		try {
			if (input != "") {
				CompPart part = HashedDictHandler::getDict().getItem(HashedDictHandler::normalize(input));
				part.setSortType(CompPart::kByPrice);

				cout << "You just bought:\n";
				cout << part << "\n\n";

				shoppingCart.add(part);
				budget -= part.getPrice();
			}

			valid = true;
		}
		catch (const char *msg) {
			cerr << msg << "\n\n";
		}
	} while (!valid);
}

void removePartFromCart(BinarySearchTree<CompPart> &shoppingCart, double &budget) {
	cout << "Your current shopping cart contains:\n";
	CompPart::printHeading(cout);
	shoppingCart.inOrderTraverse(printPart);
	cout << endl;

	HashedDictHandler::getDict().clear();
	shoppingCart.inOrderTraverse(HashedDictHandler::add);

	bool valid = false;

	do {
		cout << "Please input the name of the computer part you would like to remove, or enter nothing to go back:\n";
		string input = inputString(true);

		try {
			if (input != "") {
				CompPart part = HashedDictHandler::getDict().getItem(HashedDictHandler::normalize(input));
				cout << "You just removed:\n";
				cout << part << "\n\n";

				shoppingCart.remove(part);
				budget += part.getPrice();
			}

			valid = true;
		}
		catch (const char *msg) {
			cerr << msg << "\n\n";
		}
	} while (!valid);
}

void viewCart(BinarySearchTree<CompPart> &shoppingCart) {
	cout << "Your current shopping cart contains:\n";
	CompPart::printHeading(cout);
	shoppingCart.inOrderTraverse(printPart);
	cout << endl;
}

void changeBudget(double &budget) {
	cout << "Please enter your budget:\n";
	budget = inputNumber(0, DBL_MAX, "$");
}

void saveCart(BinarySearchTree<CompPart> &shoppingCart) {
	static const string DEFAULT_FILE_NAME = "shopping_cart.txt";
	string fileName;

	cout << "Please input the name of the file you wish to save the shopping cart in, or press ENTER to default to: " << DEFAULT_FILE_NAME << endl;
	fileName = inputString(true);

	if (fileName == "")
		fileName = DEFAULT_FILE_NAME;

	BSTHandler::file.open(fileName);
	BSTHandler::file.close();
	BSTHandler::file.open(fileName, ios::app);
	CompPart::printHeading(BSTHandler::file);
	shoppingCart.inOrderTraverse(writeToFile);
	BSTHandler::file.close();
}