#pragma once
#include "Human.h"
class elderly : public Human
{
private:
	bool chronicdiseases;
public:
	bool checkchronicdiseases() { return chronicdiseases; };
	void setchronicdiseases(bool value) { chronicdiseases = value; };
};

