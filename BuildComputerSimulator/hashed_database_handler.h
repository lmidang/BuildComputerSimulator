#pragma once
#include <string>
#include <fstream>
#include "hashed_dictionary.h"
#include "CompPartWrapper.h"
#include "queue.h"

void getNumNodes(const CompPartWrapper&);
void getSum(const CompPartWrapper&);
void writeHashToFile(const CompPartWrapper&);
void freeCompPartList(const CompPartWrapper&);

class HashedDataHandler {
private:
	static HashedDictionary<std::string, CompPartWrapper> dict;
	static int loadFactor;

public:
	static Queue<CompPartWrapper> thisList;
	static int sumOfIndex;
	static int largest;
	static std::ofstream file;

	static HashedDictionary<std::string, CompPartWrapper> & getDict();
	static std::string normalize(std::string);
	static void add(const CompPartWrapper &);
	
	static void calculateLoadFactor ();
	static int getLoadFactor();
	static int getLongestList();
	static double getAverageNodes();

	static void writeHashToFile(std::string);
	static void freeCompParts();
};