#pragma once
#include <string>
#include "hashed_dictionary.h"
#include "CompPart.h"

class HashedDictHandler {
private:
	static HashedDictionary<std::string, CompPart> dict;

public:
	static HashedDictionary<std::string, CompPart> & getDict();
	static std::string normalize(std::string);
	static void add(const CompPart &);
};