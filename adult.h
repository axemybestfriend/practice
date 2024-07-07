#pragma once
#include "Human.h"
class adult : public Human
{
private:
	bool sickday;
public:
	void setsickday(bool value) { sickday = value; };
	bool checksickday() { return sickday; };
};

