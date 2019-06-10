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
	int mPartType;
	int mSortType;
public:
	class BadSortTypeException {};

	enum partTypes  { kCPU, kCooler, kMotherBoard, kMemory, kVideoCard, kStorage, kPowerSupply};
	enum sortTypes { kByName, kByPrice, kByManufacturer, kByPowerConsumption, kByPerformanceIndex };

	CompPart();
	CompPart(std::string, std::string, double, std::string, int, int, int);
	CompPart(const CompPart&);
	virtual ~CompPart();

	// Mutators
	void setProductNumber(std::string);
	void setName(std::string);
	void setPrice(double);
	void setManufacturer(std::string);
	void setPowerConsumption(int);
	void setPerformanceIndex(int);
	void setSortType(int);

	// Accessors
	std::string getProductNumber();
	std::string getName();
	double getPrice();
	std::string getManufacturer();
	int getPowerConsumption();
	int getPerformanceIndex();
	int getPartType();
	int getSortType();

	// Overloaded Functions
	CompPart &operator=(const CompPart&);
	friend bool operator== (const CompPart&, const CompPart&);
	friend bool operator>(const CompPart&, const CompPart&);
	friend bool operator<(const CompPart&, const CompPart&);
	friend std::ostream &operator<<(std::ostream&, CompPart&);
};

