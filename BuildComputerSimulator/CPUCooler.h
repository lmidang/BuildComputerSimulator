#pragma once

#include "CompPart.h"
class CPUCooler : public CompPart
{
public:
	CPUCooler();
	CPUCooler(std::string, std::string, double, std::string, int, int, int);
	CPUCooler(const CompPart&);
	~CPUCooler();

	friend std::ostream &operator<<(std::ostream&, CPUCooler&);
};

