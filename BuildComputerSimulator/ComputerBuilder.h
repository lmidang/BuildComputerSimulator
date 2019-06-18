#pragma once
#include "CompPart.h"
#include "singly_linked_list.h"

class ComputerBuilder
{
	SinglyLinkedList<CompPart> mList;	
	int parts[8];
	std::string partsString[] = { "CPU", "CPUCooler", "Mother Board", "Memory", "Video Card", "Storage", "Case", "Power Supply" };

public:
	ComputerBuilder();
	~ComputerBuilder();

	std::string checkMissing();
	double getPrice();
	int getPower();

	bool add(CompPart&);
	bool remove(int);
};

