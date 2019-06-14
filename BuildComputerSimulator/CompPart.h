#pragma once
#include <iostream>
#include <string>

class CompPart
{
protected:
	std::string mProductNumber;
	std::string mName;
	double mPrice;
	std::string mManufacturer;
	int mPower;
	int mPerformanceIndex;
	int mPartType;
	std::string mCompatibility;
	int mSortType;	// default kByPrice
public:
	class BadSortTypeException {};

	enum partTypes  { kCPU, kCooler, kMotherBoard, kMemory, kVideoCard, kStorage, kCase, kPowerSupply};
	enum sortTypes { kByPrice, kByPerformanceIndex };

	CompPart();
	CompPart(std::string, std::string, double, std::string, int, int, int, std::string);
	CompPart(const CompPart&);
	virtual ~CompPart();

	// Mutators
	void setProductNumber(std::string);
	void setName(std::string);
	void setPrice(double);
	void setManufacturer(std::string);
	void setPowerConsumption(int);
	void setPerformanceIndex(int);
	void setCompatibility(std::string);
	void setSortType(int);

	// Accessors
	std::string getProductNumber();
	std::string getName();
	double getPrice();
	std::string getManufacturer();
	int getPowerConsumption();
	int getPerformanceIndex();
	int getPartType();
	std::string setCompatibility();
	int getSortType();

	// Overloaded Functions
	CompPart &operator=(const CompPart&);
	friend bool operator== (const CompPart&, const CompPart&);
	friend bool operator>(const CompPart&, const CompPart&);
	friend bool operator<(const CompPart&, const CompPart&);
	friend std::ostream &operator<<(std::ostream&, CompPart&);
	friend std::istream &operator>>(std::istream&, CompPart&);
};