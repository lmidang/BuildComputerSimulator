#pragma once
#include <iostream>
#include <string>

class CompPart
{
	std::string mProductNumber;
	std::string mName;
	double mPrice;
	std::string mManufacturer;
	int mPowerConsumption;
	int mPerformanceIndex;
	int mAddedOrder; // unsure if we'll keep this, it's just for the binary search tree
public:
	CompPart();
	CompPart(std::string, std::string, double, std::string, int, int, int);
	~CompPart();

	// Mutators
	void setProductNumber(std::string);
	void setName(std::string);
	void setPrice(double);
	void setManufacturer(std::string);
	void setPowerConsumption(int);
	void setPerformanceIndex(int);
	void setAddedOrder(int);

	// Accessors
	std::string getProductNumber();
	std::string getName();
	double getPrice();
	std::string getManufacturer();
	int getPowerConsumption();
	int getPerformanceIndex();
	int getAddedOrder();

	// Overloaded Functions
	friend std::ostream &operator<<(std::ostream&, CompPart&);
};

