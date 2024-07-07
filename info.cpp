#include "info.h"
#include "child.h"
#include "adult.h"
#include "elderly.h"


bool random(int percent) {
	int a = rand() % 100;
	if (a < percent)return true;
	else return false;
}

void info::connection(int i,int j)
{
	int count = arr[i][j]->getcontacts();

	while (count) 
	{
		int n = rand() % width;
		int m = rand() % height;
		if (n == i && m == j)count += 1;
		if (n >= 0 && abs(n - i) <= arr[i][j]->getTravel_radius() && n < width) {
			if (m >= 0 && abs(m - j) <= arr[i][j]->getTravel_radius() && m < height) {
				if (arr[n][m]->getstatus() == 3) {
					int r = arr[n][m]->getrisk();
					if (arr[n][m]->getvaccination() == true)r = 100 - this->vaccinaEfficacy;
					if (arr[i][j]->getmask() == true)r = r / 2;
				    if (arr[n][m]->getmask() == true)r = r / 2;

					if (child* obj = dynamic_cast<child*>(arr[n][m])) 
					{
						if (obj->checkcarrier() == true && random(r))
						{
							arr[n][m]->setstatus(2);
							arr[n][m]->sethealth(0);
							this->NumberOfCases += 1;
						};
					}
					else if (adult* obj = dynamic_cast<adult*>(arr[n][m])) 
					{
						if (random(r))
						{
							arr[n][m]->setstatus(2);
							arr[n][m]->sethealth(0);
							this->NumberOfCases += 1;
						};
					}
					else if (elderly* obj = dynamic_cast<elderly*>(arr[n][m])) 
					{
						if (random(r))
						{
							arr[n][m]->setstatus(2);
							arr[n][m]->sethealth(0);
							this->NumberOfCases += 1;
						};
					}
				}
				count -= 1;
			}
		}
	}
}




int info::step()
{
	for (size_t i = 0; i < width; i++)
	{
		for (size_t j = 0; j < height; j++)
		{
			if (arr[i][j]->getstatus() == 1)
			{
				if (adult* obj = dynamic_cast<adult*>(arr[i][j])) {
					if (obj->checksickday() == true)continue;
				}
				connection(i, j);
			}
			else if ((arr[i][j]->getstatus() == 2 && arr[i][j]->gethealth() != 0))
			{	
				if (child* obj = dynamic_cast<child*>(arr[i][j]))
				{
					if (obj->checkcarrier() == false)continue;
				}
				connection(i, j);
			}
		}
	}


	for (size_t i = 0; i < width; i++)
	{
		for (size_t j = 0; j < height; j++)
		{
			if (arr[i][j]->getstatus() == 2) 
			{
				arr[i][j]->sethealth(arr[i][j]->gethealth() + 1);
				if (arr[i][j]->gethealth() > arr[i][j]->getincubation()) 
				{
					this->NumberOfPatients += 1;
					arr[i][j]->setstatus(1);
					arr[i][j]->sethealth(0);
				}
			}
			if (arr[i][j]->getstatus() == 1) {
				arr[i][j]->sethealth(arr[i][j]->gethealth() + 1);
				if (arr[i][j]->gethealth() > arr[i][j]->getperiodOfIllness()) 
				{
					if (hospitalcapacity < NumberOfPatients) {
						if (elderly* obj = dynamic_cast<elderly*>(arr[i][j])) {
							if (obj->checkchronicdiseases() == true)
							{
								if (random(chronomortality * 2))arr[i][j]->setstatus(-1);
								else arr[i][j]->setstatus(0);
							}
							else
							{
								if (random(obj->getfatal() * 2))arr[i][j]->setstatus(-1);
								else arr[i][j]->setstatus(0); 
							}
						}
						else {
							if (random(arr[i][j]->getfatal() * 2))
							{
								arr[i][j]->setstatus(-1);
							}
							else
							{
								arr[i][j]->setstatus(0);
							}
						}
					}
					else {
						if (elderly* obj = dynamic_cast<elderly*>(arr[i][j])) {
							if (obj->checkchronicdiseases() == true)
							{
								if (random(this->chronomortality))arr[i][j]->setstatus(-1);
								else arr[i][j]->setstatus(0);
							}
							else
							{
								if (random(obj->getfatal()))arr[i][j]->setstatus(-1);
								else arr[i][j]->setstatus(0);
							}
						}
						else {
							if (random(arr[i][j]->getfatal()))
							{
								arr[i][j]->setstatus(-1);
							}
							else
							{
								arr[i][j]->setstatus(0);
							}
						}
					}
					arr[i][j]->sethealth(0);
					this->NumberOfCases -= 1;
					this->NumberOfPatients -= 1;
				}
			}
		}
	}
	return this->NumberOfCases;
}
info::info()
{
	vector<vector<Human*>> ilv(100, vector<Human*>(100));
	this->arr = ilv;
	this->width = 0;
	this->height = 0;
}
