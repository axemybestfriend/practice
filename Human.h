#pragma once

#include "ofxGui.h"
#include "D:\of_v0.12.0_vs_release\apps\myApps\practice\cell.h"

class Human
{
private:
	int status;
	int health;
	int travel_radius;
	int contacts;
	int risk;
	int incubation;
	int periodOfIllness;
	int fatal;
	bool mask;
	bool vaccination;
public:
	cell button;
	
	int gethealth() { return health; };
	void sethealth(int value) { health = value; };

	int getstatus() { return status; };
	void setstatus(int value) { status = value; };

	int getcontacts() { return contacts; };
	void setcontacts(int value) { contacts = value; };

	int getTravel_radius() { return travel_radius; };
	void setTravel_radius(int value) { travel_radius = value; };

	bool getmask() { return mask; };
	void setmask(bool value) { mask = value; };

	bool getvaccination() { return vaccination; };
	void setvaccination(bool value) { vaccination = value; };

	int getrisk() { return risk; };
	void setrisk(int value) { risk = value; };

	int getfatal() { return fatal; };
	void setfatal(int value) { fatal = value; };

	int getincubation() { return incubation; };
	void setincubation(int value) { incubation = value; };

	int getperiodOfIllness() { return periodOfIllness; };
	void setperiodOfIllness(int value) { periodOfIllness = value; };

	virtual ~Human(){}
};

