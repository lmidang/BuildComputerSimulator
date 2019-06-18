#include "hashed_database_handler.h"

HashedDictionary<std::string, CompPart> HashedDataHandler::dict = HashedDictionary<std::string, CompPart>();

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