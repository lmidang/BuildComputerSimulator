#include <iostream>
#include <fstream>
#include "input_tools.h"
#include "BSTHandler.h"
#include "hashed_dict_handler.h"

using namespace std;

void readFromFile(BSTHandler &);
void addPartToCart(BSTHandler &, BinarySearchTree<CompPart> &, double &);
void removePartFromCart(BinarySearchTree<CompPart> &, double &);
void changeBudget(double &);
void viewCart(BinarySearchTree<CompPart> &);
void saveCart(BinarySearchTree<CompPart> &);

int main()
{
	BSTHandler bstHandler;
	BinarySearchTree<CompPart> shoppingCart;
	readFromFile(bstHandler);

	string menuOptions[] = {
		"Add computer part to shopping cart",
		"Remove computer part from shopping cart",
		"View shopping cart",
		"Change budget",
		"Exit"
	};

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
		CompPart item;
		inFile >> item;

		bstHandler.add(item);
	}

	inFile.close();
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