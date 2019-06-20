/*
Worked on by Bennett Zhang
*/

#pragma once
#include <string>
#include "hashed_dictionary.h"
#include "CompPartWrapper.h"

class HashedDictHandler {
private:
	static HashedDictionary<std::string, CompPartWrapper> dict;

public:
	static HashedDictionary<std::string, CompPartWrapper> & getDict();
	static std::string normalize(std::string);
	static void add(const CompPartWrapper &);
};