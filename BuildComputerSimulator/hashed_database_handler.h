#pragma once
#include <string>
#include <fstream>
#include "hashed_dictionary.h"
#include "CompPart.h"

void getNumNodes(const CompPart&);
void getSum(const CompPart&);
void writeHashToFile(const CompPart&);

class HashedDataHandler {
private:
	static HashedDictionary<std::string, CompPart> dict;
	static int loadFactor;

public:
	static int sumOfIndex;
	static int largest;
	static std::ofstream file;

	static HashedDictionary<std::string, CompPart> & getDict();
	static std::string normalize(std::string);
	static void add(const CompPart &);
	
	static void calculateLoadFactor ();
	static int getLoadFactor();
	static int getLongestList();
	static double getAverageNodes();

	static void writeHashToFile(std::string);
};