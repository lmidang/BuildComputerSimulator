#include "CompPart.h"

const std::string CompPart::partNames[] = { "CPU", "Cooler", "Motherboard", "Memory", "Video Card", "Storage", "Case", "Power Supply" };
const size_t CompPart::NUM_PARTS = 8;

CompPart::CompPart()
{
	mName = "";
	mPrice = 0;
	mManufacturer = "";
	mPower = 0;
	mPerformanceIndex = -1;
	mPartType = -1;
	mCompatibility = "";
	mSortType = kByPrice;
}

CompPart::CompPart(std::string name, double price, std::string manufacturer, int power,
	int performance, int partType, std::string compatibility) {
	mName = name;
	mPrice = price;
	mManufacturer = manufacturer;
	mPower = power;
	mPerformanceIndex = performance;
	mPartType = partType;
	mCompatibility = compatibility;
	mSortType = kByPrice;
}

CompPart::CompPart(const CompPart& cp) {
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

std::string CompPart::getName() const {
	return mName;
}

double CompPart::getPrice() const {
	return mPrice;
}

std::string CompPart::getManufacturer() const {
	return mManufacturer;
}

int CompPart::getPower() const {
	return mPower;
}

int CompPart::getPerformanceIndex() const {
	return mPerformanceIndex;
}

int CompPart::getPartType() const {
	return mPartType;
}

int CompPart::getSortType() const {
	return mSortType;
}

std::string CompPart::getCompatibility() const {
	return mCompatibility;
}

CompPart& CompPart::operator=(const CompPart &cp) {
	if (!(*this == cp)) {
		mName = cp.mName;
		mPrice = cp.mPrice;
		mManufacturer = cp.mManufacturer;
		mPower = cp.mPower;
		mPerformanceIndex = cp.mPerformanceIndex;
		mPartType = cp.mPartType;
		mCompatibility = cp.mCompatibility;
		mSortType = cp.mSortType;
	}
	return *this;
}

bool operator==(const CompPart& cp1, const CompPart& cp2) {
	return (cp1.mName == cp2.mName) &&
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

std::ostream & CompPart::printHeading(std::ostream &os) {
	os << std::left << std::setw(12) << "Part Type" << " || " << std::setw(19) << "Name" <<  " || " << std::setw(15);
	os << "Manufacturer" <<  " || " << std::setw(9) << "Price" <<  " || " << "Performance Index" << std::endl;
	os << "========================================================================================" << std::endl;
	return os;
}

std::ostream &operator<<(std::ostream &os, const CompPart &cp) {
	os << std::left << std::setw(12) << CompPart::partNames[cp.mPartType] << " || ";
	os << std::setw(19) << cp.mName << " || ";
	os << std::setw(15) << cp.mManufacturer << " || ";
	os << '$' << std::right << std::setw(8) << std::setprecision(2) << std::fixed << cp.mPrice << " || ";
	os << std::setprecision(0) << cp.mPerformanceIndex;
	return os;
}

std::istream &operator>>(std::istream &is, CompPart &cp) {
	cp = CompPart();

	std::string line;
	std::getline(is, line);
	cp.mPartType = stoi(line.substr(0, line.find(',')));

	line = line.substr(line.find(',') + 1);
	cp.mName = line.substr(0, line.find(','));
	
	line = line.substr(line.find(',') + 1);
	cp.mPrice = stod(line.substr(0, line.find(',')));
	
	line = line.substr(line.find(',') + 1);
	cp.mManufacturer = line.substr(0, line.find(','));
	
	line = line.substr(line.find(',') + 1);
	cp.mPower = stoi(line.substr(0, line.find(',')));
	
	line = line.substr(line.find(',') + 1);
	cp.mPerformanceIndex = stoi(line.substr(0, line.find(',')));
	if ((cp.mPartType == CompPart::kCPU) || (cp.mPartType == CompPart::kMotherBoard)) {	// check this later
		line = line.substr(line.find(',') + 1);
		cp.mCompatibility = line.substr(0, line.find(','));
	}
	else {
		cp.mCompatibility == "";
	}
	return is;
}