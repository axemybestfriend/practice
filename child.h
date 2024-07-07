#pragma once
#include "Human.h"
class child : public Human
{
private:
	bool carrier;
public:
	bool checkcarrier() { return carrier; };
	void setcarrier(int value) { carrier = value; };
};

