#pragma once

#include "CompPart.h"
class PowerSupply : public CompPart 
{
public:
	PowerSupply();
	PowerSupply(std::string, std::string, double, std::string, int, int, int);
	PowerSupply(const CompPart&);
	~PowerSupply();

	friend std::ostream &operator<<(std::ostream&, PowerSupply&);
};

