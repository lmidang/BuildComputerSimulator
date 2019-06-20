/*
Worked on by Bennett Zhang
*/

#include "hashed_dict_handler.h"

HashedDictionary<std::string, CompPartWrapper> HashedDictHandler::dict = HashedDictionary<std::string, CompPartWrapper>(31);

HashedDictionary<std::string, CompPartWrapper> & HashedDictHandler::getDict() {
	return dict;
}

// Returns a string with all spaces stripped out and all letters converted to uppercase
std::string HashedDictHandler::normalize(std::string name) {
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

// Add an item to the hash table
void HashedDictHandler::add(const CompPartWrapper &item) {
	dict.add(normalize(item.get().getName()), item);
}
