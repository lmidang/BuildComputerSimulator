#pragma once
#include "CompPart.h"

class CompPartWrapper
{
	CompPart* compP;
public:
	CompPartWrapper();
	CompPartWrapper(CompPart*);
	CompPartWrapper(const CompPartWrapper&);
	~CompPartWrapper();

	void freeComp();
	CompPart& get() const;
	CompPart* getPtr() const;

	CompPartWrapper& operator=(const CompPartWrapper&);
	friend std::ostream &operator<<(std::ostream& os, const CompPartWrapper& cp);
	friend std::istream &operator>>(std::istream& is, CompPartWrapper& cp);
	friend bool operator== (const CompPartWrapper& cp1, const CompPartWrapper& cp2);
};

