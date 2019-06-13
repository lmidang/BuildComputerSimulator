#pragma once

#include "CompPart.h"
class VideoCard : public CompPart
{
public:
	VideoCard();
	VideoCard(std::string, std::string, double, std::string, int, int, int);
	VideoCard(const CompPart&);
	~VideoCard();

	friend std::ostream &operator<<(std::ostream&, VideoCard&);
};

