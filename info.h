#pragma once

#include "ofMain.h"
#include "Human.h"


class info
{
public:
	int width;
	int height;
	int countOfChild;
	int countOfAdult;
	int countOfElderly;
	int NumberOfCases;
	int NumberOfPatients;
	int hospitalcapacity;
	int vaccination;
	int vaccinaEfficacy;
	int mask;
	int chronosick;
	int sickday;
	int carrier;
	int chronomortality;

	bool flagstartmodel;

	vector<vector<Human*>> arr;
	void connection(int i, int j);
	int step();
	info();
};