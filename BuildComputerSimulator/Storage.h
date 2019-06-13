#pragma once

#include "CompPart.h"
class Storage : public CompPart
{
public:
	Storage();
	Storage(std::string, std::string, double, std::string, int, int, int);
	Storage(const CompPart&);
	virtual ~Storage();

	friend std::ostream &operator<<(std::ostream&, Storage&);
};



