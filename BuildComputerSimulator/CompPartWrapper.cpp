#include "CompPartWrapper.h"

CompPartWrapper::CompPartWrapper() {
	compP = nullptr;
}

CompPartWrapper::CompPartWrapper(CompPart* cp) {
	compP = cp;
}

CompPartWrapper::CompPartWrapper(const CompPartWrapper &cp) {
	compP = cp.compP;
}

void CompPartWrapper::freeComp() {
	if (compP != nullptr) {
		delete compP;
		compP = nullptr;
	}
}

CompPart& CompPartWrapper::get() const{
	return *compP;
}

CompPart* CompPartWrapper::getPtr() const {
	return compP;
}

CompPartWrapper::~CompPartWrapper()
{
//	freeComp();
	compP = nullptr;
}

CompPartWrapper& CompPartWrapper::operator=(const CompPartWrapper&cp) {
	if (!(*this == cp)) {
		compP = cp.compP;
	}
	return *this;
}

std::ostream &operator<<(std::ostream& os, const CompPartWrapper& cp) {
	os << *cp.compP;
	return os;
}

std::istream &operator>>(std::istream& is, CompPartWrapper& cp) {
	cp.compP = new CompPart();
	is >> *(cp.compP);
	return is;
}

bool operator== (const CompPartWrapper& cp1, const CompPartWrapper& cp2) {
	return (cp1.compP != nullptr) && (cp2.compP != nullptr) && (*(cp1.compP) == *(cp2.compP));
}
