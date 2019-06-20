#include "hashed_dict_handler.h"

HashedDictionary<std::string, CompPart> HashedDictHandler::dict = HashedDictionary<std::string, CompPart>(31);

HashedDictionary<std::string, CompPart> & HashedDictHandler::getDict() {
	return dict;
}

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

void HashedDictHandler::add(const CompPart &item) {
	dict.add(normalize(item.getName()), item);
}
