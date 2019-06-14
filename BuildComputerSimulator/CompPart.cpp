#include "CompPart.h"

CompPart::CompPart()
{
	mProductNumber = "";
	mName = "";
	mPrice = 0;
	mManufacturer = "";
	mPower = 0;
	mPerformanceIndex = -1;
	mPartType = -1;
	mCompatibility = "";
	mSortType = 0;
}

CompPart::CompPart(std::string productNum, std::string name, double price, std::string manufacturer, int power,
	int performance, int partType, std::string compatibility) {
	mProductNumber = productNum;
	mName = name;
	mPrice = price;
	mManufacturer = manufacturer;
	mPower = power;
	mPerformanceIndex = performance;
	mPartType = partType;
	mCompatibility = compatibility;
	mSortType = 0;
}

CompPart::CompPart(const CompPart& cp) {
	mProductNumber = cp.mProductNumber;
	mName = cp.mName;
	mPrice = cp.mPrice;
	mManufacturer = cp.mManufacturer;
	mPower = cp.mPower;
	mPerformanceIndex = cp.mPerformanceIndex;
	mPartType = cp.mPartType;
	mCompatibility = cp.mCompatibility;
	mSortType = cp.mSortType;
}

CompPart::~CompPart()
{
}

void CompPart::setProductNumber(std::string s) {
	mProductNumber = s;
}

void CompPart::setName(std::string s) {
	mName = s;
}

void CompPart::setPrice(double p) {
	mPrice = p;
}

void CompPart::setManufacturer(std::string s) {
	mManufacturer = s;
}

void CompPart::setPower(int i) {
	mPower = i;
}

void CompPart::setPerformanceIndex(int i) {
	mPerformanceIndex = i;
}

void CompPart::setCompatibility(std::string s) {
	mCompatibility = s;
}

void CompPart::setSortType(int i) {
	mSortType = i;
}

std::string CompPart::getProductNumber() {
	return mProductNumber;
}

std::string CompPart::getName() {
	return mName;
}

double CompPart::getPrice() {
	return mPrice;
}

std::string CompPart::getManufacturer() {
	return mManufacturer;
}

int CompPart::getPower() {
	return mPower;
}

int CompPart::getPerformanceIndex() {
	return mPerformanceIndex;
}

int CompPart::getPartType() {
	return mPartType;
}

int CompPart::getSortType() {
	return mSortType;
}

std::string CompPart::getCompatibility() {
	return mCompatibility;
}

CompPart& CompPart::operator=(const CompPart &cp) {
	if (!(*this == cp)) {
		mProductNumber = cp.mProductNumber;
		mName = cp.mName;
		mPrice = cp.mPrice;
		mManufacturer = cp.mManufacturer;
		mPower = cp.mPower;
		mPartType = cp.mPartType;
		mSortType = cp.mSortType;
		mCompatibility = cp.mCompatibility;
	}
	return *this;
}

bool operator==(const CompPart& cp1, const CompPart& cp2) {
	return (cp1.mProductNumber == cp2.mProductNumber) && (cp1.mName == cp2.mName) &&
		(cp1.mPrice == cp2.mPrice) && (cp1.mManufacturer == cp2.mManufacturer) &&
		(cp1.mPower == cp2.mPower) &&
		(cp1.mPerformanceIndex == cp2.mPerformanceIndex) &&
		(cp1.mPartType == cp2.mPartType) &&
		(cp1.mCompatibility == cp2.mCompatibility);
}

bool operator>(const CompPart& cp1, const CompPart& cp2) {
	if (cp1.mSortType != cp2.mSortType) {
		throw CompPart::BadSortTypeException();
	}
	switch (cp1.mSortType) {
	case CompPart::kByPrice:
		return cp1.mPrice > cp2.mPrice;
		break;
	case CompPart::kByPerformanceIndex:
		return cp1.mPerformanceIndex > cp2.mPerformanceIndex;
	default:
		throw CompPart::BadSortTypeException();
	}
}

bool operator<(const CompPart& cp1, const CompPart& cp2) {
	if (cp1.mSortType != cp2.mSortType) {
		throw CompPart::BadSortTypeException();
	}
	switch (cp1.mSortType) {
	case CompPart::kByPrice:
		return cp1.mPrice < cp2.mPrice;
		break;
	case CompPart::kByPerformanceIndex:
		return cp1.mPerformanceIndex < cp2.mPerformanceIndex;
	default:
		throw CompPart::BadSortTypeException();
	}
}

std::ostream &operator<<(std::ostream &os, CompPart &cp) { // prob fix this later
	os << cp.mName << " " << cp.mPartType << " " << cp.mManufacturer << " " << cp.mPrice;
	return os;
}

std::istream &operator>>(std::istream &is, CompPart &cp) {
	cp = CompPart();

	std::string line;
	std::getline(is, line);
	cp.mPartType = stoi(line.substr(line.find(',') + 1));

	line = line.substr(line.find(',') + 1);
	cp.mName = line.substr(line.find(',') + 1);
	
	line = line.substr(line.find(',') + 1);
	cp.mPrice = stod(line.substr(line.find(',') + 1));
	
	line = line.substr(line.find(',') + 1);
	cp.mManufacturer = line.substr(line.find(',') + 1);
	
	line = line.substr(line.find(',') + 1);
	cp.mPower = stoi(line.substr(line.find(',') + 1));
	
	line = line.substr(line.find(',') + 1);
	cp.mPerformanceIndex = stoi(line.substr(line.find(',') + 1));
	if ((cp.mPartType == CompPart::kCPU) || (cp.mPartType == CompPart::kMotherBoard)) {	// check this later
		line = line.substr(line.find(',') + 1);
		cp.mCompatibility = line.substr(line.find(',') + 1);
	}
	return is;
}