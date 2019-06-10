#include "CompPart.h"



CompPart::CompPart()
{
	mProductNumber = "";
	mName = "";
	mPrice = 0;
	mManufacturer = "";
	mPowerConsumption = 0;
	mPerformanceIndex = -1;
	mPartType = -1;
	mSortType = 0;
}

CompPart::CompPart(std::string productNum, std::string name, double price, std::string manufacturer, int power, 
	int performance, int partType) {
	mProductNumber = productNum;
	mName = name;
	mPrice = price;
	mManufacturer = manufacturer;
	mPowerConsumption = power;
	mPerformanceIndex = performance;
	mPartType = partType;
	mSortType = 0;
}

CompPart::CompPart(const CompPart& cp) {
	mProductNumber = cp.mProductNumber;
	mName = cp.mName;
	mPrice = cp.mPrice;
	mManufacturer = cp.mManufacturer;
	mPowerConsumption = cp.mPowerConsumption;
	mPerformanceIndex = cp.mPerformanceIndex;
	mPartType = cp.mPartType;
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

void CompPart::setPowerConsumption(int i) {
	mPowerConsumption = i;
}

void CompPart::setPerformanceIndex(int i) {
	mPerformanceIndex = i;
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

int CompPart::getPowerConsumption() {
	return mPowerConsumption;
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

CompPart& CompPart::operator=(const CompPart &cp) {
	if (!(*this == cp)) {
		mProductNumber = cp.mProductNumber;
		mName = cp.mName;
		mPrice = cp.mPrice;
		mManufacturer = cp.mManufacturer;
		mPowerConsumption = cp.mPowerConsumption;
		mPartType = cp.mPartType;
		mSortType = cp.mSortType;
	}
	return *this;
}

bool operator==(const CompPart& cp1, const CompPart& cp2) {
	return (cp1.mProductNumber == cp2.mProductNumber) && (cp1.mName == cp2.mName) &&
		(cp1.mPrice == cp2.mPrice) && (cp1.mManufacturer == cp2.mManufacturer) &&
		(cp1.mPowerConsumption == cp2.mPowerConsumption) &&
		(cp1.mPerformanceIndex == cp2.mPerformanceIndex) &&
		(cp1.mPartType == cp2.mPartType) &&
		(cp1.mSortType == cp2.mSortType);
}

bool operator>(const CompPart& cp1, const CompPart& cp2) {
	if (cp1.mSortType != cp2.mSortType) {
		throw CompPart::BadSortTypeException();
	}
	switch (cp1.mSortType) {
	case CompPart::kByName:
		return cp1.mName > cp2.mName;
		break;
	case CompPart::kByPrice:
		return cp1.mPrice > cp2.mPrice;
		break;
	case CompPart::kByManufacturer:
		return cp1.mManufacturer > cp2.mManufacturer;
		break;
	case CompPart::kByPowerConsumption:
		return cp1.mPowerConsumption > cp2.mPowerConsumption;
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
	case CompPart::kByName:
		return cp1.mName < cp2.mName;
		break;
	case CompPart::kByPrice:
		return cp1.mPrice < cp2.mPrice;
		break;
	case CompPart::kByManufacturer:
		return cp1.mManufacturer < cp2.mManufacturer;
		break;
	case CompPart::kByPowerConsumption:
		return cp1.mPowerConsumption < cp2.mPowerConsumption;
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