#include "hashed_dict_handler.h"

HashedDictionary<std::string, CompPartWrapper> HashedDictHandler::dict = HashedDictionary<std::string, CompPartWrapper>(31);

HashedDictionary<std::string, CompPartWrapper> & HashedDictHandler::getDict() {
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

void HashedDictHandler::add(const CompPartWrapper &item) {
	dict.add(normalize(item.get().getName()), item);
}
