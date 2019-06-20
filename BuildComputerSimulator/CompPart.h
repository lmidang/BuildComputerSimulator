/*
Worked on by Lynn Dang
*/

#pragma once
#include <iostream>
#include <iomanip>
#include <string>

class CompPart
{
protected:
	std::string mName;
	double mPrice;
	std::string mManufacturer;
	int mPower;
	int mPerformanceIndex;
	int mPartType;
	std::string mCompatibility;
public:
	class BadSortTypeException {};
	class ExtraSpaceException {};

	enum partTypes { kCPU, kCooler, kMotherBoard, kMemory, kVideoCard, kStorage, kCase, kPowerSupply };

	const static std::string partNames[];
	const static size_t NUM_PARTS;

	CompPart();
	CompPart(std::string, double, std::string, int, int, int, std::string);
	CompPart(const CompPart&);
	virtual ~CompPart();

	// Mutators
	void setName(std::string);
	void setPrice(double);
	void setManufacturer(std::string);
	void setPower(int);
	void setPerformanceIndex(int);
	void setCompatibility(std::string);
	void setPartType(int);

	// Accessors
	std::string getName() const;
	double getPrice() const;
	std::string getManufacturer() const;
	int getPower() const;
	int getPerformanceIndex() const;
	int getPartType() const;
	std::string getCompatibility() const;

	static std::ostream & printHeading(std::ostream &);

	// Overloaded Functions
	CompPart &operator=(const CompPart&);
	friend bool operator== (const CompPart&, const CompPart&);
	friend std::ostream &operator<<(std::ostream&, const CompPart&);
	friend std::istream &operator>>(std::istream&, CompPart&);
};