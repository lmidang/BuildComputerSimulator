#include <iostream>
#include <fstream>
#include "input_tools.h"
#include "BSTHandler.h"
#include "hashed_dict_handler.h"
#include "hashed_database_handler.h"

using namespace std;

void readFromFile(BSTHandler &);
void printItem(CompPart const &);
void addPartToCart(BSTHandler &, BinarySearchTree<CompPart, string> &, double &);
void removePartFromCart(BinarySearchTree<CompPart, string> &, double &);
void changeBudget(double &);
void viewCart(BinarySearchTree<CompPart, string> &);
void saveCart(BinarySearchTree<CompPart, string> &);

int main()
{
	// Create file name, bst handler, and read from file
	const string DEFAULT_FILE_NAME = "data.csv";
	BSTHandler *bstHandler = new BSTHandler();
	readFromFile(*bstHandler);
	// Completely done when true 
	bool isCompletelyDone = false;

	// Main/Menu options 
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
		cout << endl;
		
		// Ask user for input option using switch 
		switch (userOption) {
		case 0: {
			bool isEditingDatDone = false;
			do {
				string editingOptions[] = { "Add Data", "Remove Data", "Search by Name", "List in Hash Sequence", "List in Key Sequence", "List by Price", "List by Performance", "Efficiency", "Exit" };
				cout << endl;
				size_t editingChoice = menu(editingOptions, 9);
				cout << endl;

				switch(editingChoice) {
				case 0: { // add
					string stringInput;
					int intInput;
					double doubleInput;

					// Create new component part of type CompPart
					// Ask user for input, set data 
					CompPart newCompPart;
					cout << "Select the part type from the menu:" << endl;
					intInput = menu(CompPart::partNames, CompPart::NUM_PARTS);
					cout << endl;
					newCompPart.setPartType(intInput);
					cout << "Enter a name: ";
					stringInput = inputString();
					newCompPart.setName(stringInput);
					cout << "Enter a price: ";
					doubleInput = inputNumber(0, DBL_MAX, "$");
					newCompPart.setPrice(doubleInput);
					cout << "Enter the manufacturer: ";
					stringInput = inputString();
					newCompPart.setManufacturer(stringInput);
					cout << "Enter the power: ";
					intInput = int(inputNumber(0, DBL_MAX));
					newCompPart.setPower(intInput);
					cout << "Enter the performanceIndex: ";
					intInput = int(inputNumber(0, DBL_MAX));
					newCompPart.setPerformanceIndex(intInput);
					if ((newCompPart.getPartType() == CompPart::kCPU) || (newCompPart.getPartType() == CompPart::kMotherBoard)) {
						cout << "Enter compatibility: ";
						stringInput = inputString(true);
						newCompPart.setCompatibility(stringInput);
					}

					cout << "Here is the computer part you added:\n";
					cout << newCompPart << endl;

					bstHandler->add(newCompPart);
					HashedDataHandler::add(newCompPart);
					break;
				}
				case 1: { // remove by name
					cout << "Enter the name of the part: " << endl;
					string userInput;
					userInput = inputString();
					try {
						CompPart toDelete = HashedDataHandler::getDict().getItem(HashedDataHandler::normalize(userInput));
						bstHandler->remove(toDelete);
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
					CompPart::printHeading(cout);
					HashedDataHandler::getDict().traverse(printItem);
					break;
				}
				case 4: { // list key sequence
					cout << "Enter an index:\n";
					size_t inputNum = static_cast<size_t>(inputNumber(0, HashedDataHandler::getDict().getSize() - 1));
					CompPart::printHeading(cout);
					try {
						HashedDataHandler::getDict().traverseIndex(printItem, inputNum);
					}
					catch (HashedDictionary<string, CompPart>::OutOfRangeException) {
						cerr << "Index is out of range!\n";
					}
					break;
				}
				case 5: { // list price
					string displayType[] = { "By Price", "Indented" };
					size_t displayChoice = menu(displayType, 2);
					cout << endl;

					switch (displayChoice) {
					case 0:
						bstHandler->displayListByPrice();
						break;
					case 1:
						bstHandler->displayListByPriceIndented();
						break;
					default:
						cout << "invalid input\n" << endl;
						break;
					}
					break;
				}
				case 6: { // list performance
					string displayType[] = { "By Performance", "Indented" };
					size_t displayChoice = menu(displayType, 2);
					cout << endl;

					switch (displayChoice) {
					case 0:
						bstHandler->displayListByPerformance();
						break;
					case 1:
						bstHandler->displayListByPerformanceIndented();
						break;
					default:
						cout << "invalid input\n" << endl;
						break;
					}
					break;
				}
				case 7: { // efficiency
					string displayEfficiency[] ={ "Load factor", "Longest linked list", "Average nodes per list" };
					int userChoice = menu(displayEfficiency, 3);
					cout << endl;

					switch (userChoice) {
					case 0:
						cout << "Load factor PriceBST: " << bstHandler->getPriceLoadFactor() << endl;
						cout << "Load factor PerformanceBST: " << bstHandler->getPerformanceLoadFactor() << endl;
						cout << "Load factor Hashed Table: " << HashedDataHandler::getLoadFactor() << endl;
						break;
					case 1:
						cout << "Longest list: " << HashedDataHandler::getLongestList() << endl;
						break;
					case 2:
						cout << "Average nodes: " << HashedDataHandler::getAverageNodes() << endl;
						break;
					default:
						cout << "Invalid input\n";
					}
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
					HashedDataHandler::writeHashToFile(fileName);

					break;
				}
				default:
					cout << "Invalid input.\n\n";
				}
			} while (!isEditingDatDone);
			break;
		}
		case 1: {	// build computer option here
			BinarySearchTree<CompPart, string> *shoppingCart = new BinarySearchTree<CompPart, string>();
			double budget;
			changeBudget(budget);

			bool exit = false;

			do {
				size_t menuChoice = menu(menuOptions, 5);
				cout << endl;

				switch (menuChoice) {
				case 0:
					addPartToCart(*bstHandler, *shoppingCart, budget);
					break;
				case 1:
					removePartFromCart(*shoppingCart, budget);
					break;
				case 2:
					viewCart(*shoppingCart);
					break;
				case 3:
					changeBudget(budget);
					break;
				case 4:
					saveCart(*shoppingCart);
					delete shoppingCart;
					shoppingCart = nullptr;
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

	delete bstHandler;
	bstHandler = nullptr;
	system("pause");
	return 0;
}

/*
Return void
readFromFile, param BSTHandler and &bstHandler
read in from file, create default file name
bool valid, false until inFile
Ask user for file name, if file is not there return invalid 
Read data from file into item CompPart 
*/
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

	HashedDataHandler::calculateLoadFactor();
	bstHandler.calculateFactor();
}

// Print func, cout CompPart const &cp, cout cp
void printItem(CompPart const &cp) {
	cout << cp << endl;
}

/*
Return void, func addPartToCart
BSTHandler &bstHandler, BST<CompPart> &shoppingCart, &budget
Display items and ask user which part is desired
Ask user desired type of sort
SinglyLinkedList type CompPart partsList
Use switch for sort choice
Return output according to user's budget (ex: too low)
Output user's purchase after getItem
*/
void addPartToCart(BSTHandler &bstHandler, BinarySearchTree<CompPart, string> &shoppingCart, double &budget) {
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

				cout << "You just bought:\n";
				cout << part << "\n\n";

				shoppingCart.add(part, part.getName());
				budget -= part.getPrice();
			}

			valid = true;
		}
		catch (const char *msg) {
			cerr << msg << "\n\n";
		}
	} while (!valid);
}
/*
return void
func removePartFromCart
BinarySearchTree<CompPart> &shoppingCart, double &budget
Display current shopping cart in order traverse
Ask user to enter name of part they would like to remove
If input is not empty then show user which part removed from list
Remove from shopping cart and adjust running total 
*/
void removePartFromCart(BinarySearchTree<CompPart, string> &shoppingCart, double &budget) {
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

				shoppingCart.remove(part, part.getName());
				budget += part.getPrice();
			}

			valid = true;
		}
		catch (const char *msg) {
			cerr << msg << "\n\n";
		}
	} while (!valid);
}

/*
return void
func viewCart 
BinarySearchTree<CompPart> &shoppingCart
cout shopping cart:
print shoppingCart in order traverse
*/
void viewCart(BinarySearchTree<CompPart, string> &shoppingCart) {
	cout << "Your current shopping cart contains:\n";
	CompPart::printHeading(cout);
	shoppingCart.inOrderTraverse(printPart);
	cout << endl;
}

/*
return void
func changeBudget
double &budget
cout enter your budget
user input number, 0, max, and $ assign to budget
*/
void changeBudget(double &budget) {
	cout << "Please enter your budget:\n";
	budget = inputNumber(0, DBL_MAX, "$");
}

/*
return void
func saveCart
BSTtree<CompPart> &shoppingCart
file name, shopping cart, string fileName
Ask user to enter the name of file save location
BST: open file, close, open app, print heading bst file, write shopping cart in order traverse to file, close file
*/
void saveCart(BinarySearchTree<CompPart, string> &shoppingCart) {
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