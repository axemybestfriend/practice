#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	sliderGroup.setName("Customization");
	sliderGroup.add(sizex.set("Width", 25, 10, 50));
	sliderGroup.add(sizey.set("Height", 25, 10, 30));
	sliderGroup.add(radius.set("Travel radius ", 5, 1, 10));
	sliderGroup.add(contact.set("Contacts per day", 5, 1, 8));
	sliderGroup.add(transmission.set("Transmission rate", 15, 1, 100));
	sliderGroup.add(incubation.set("Incubation", 5, 0, 10));
	sliderGroup.add(periodOfIllness.set("Period of illness", 5, 1, 10));
	sliderGroup.add(mortality.set("Mortality rate", 5, 1, 100));
	sliderGroup.add(hospital.set("Hospital capacity", 30, 1, 100));

	sliderGroup2.setName("Immutable parameters");
	sliderGroup2.add(mask.set("Mask percent", 5, 0, 100));	
	sliderGroup2.add(vaccination.set("Vaccination percent", 15, 0, 100));
	sliderGroup2.add(vaccineEfficacy.set("Vaccination efficacy(chance get sick)", 97, 0, 100));
	sliderGroup2.add(carrier.set("Percent carrier children", 5, 0, 100));
	sliderGroup2.add(sickday.set("Percent of adults with sick leave", 5, 1, 100));
	sliderGroup2.add(chrosick.set("Percentage of chronic diseases", 5, 1, 100));
	sliderGroup2.add(chronomortality.set("Mortality rate with chronic diseases", 70, 1, 100));

	resetButton.set(400,10,80,35);

	startButton.set(485, 10, 40, 35);
	bstartButton = false;

	stepButton.set(530, 10, 80, 35);


	white.set(20, 420, 20, 20);
	black.set(20, 460, 20, 20);
	gold.set(20, 500, 20, 20);
	pink.set(20, 540, 20, 20);
	red.set(20, 580, 20, 20);
	blue.set(20, 620, 20, 20);
	green.set(20, 660, 20, 20);
	gray.set(20, 700, 20, 20);

	panel.setup(sliderGroup);
	panel2.setup(sliderGroup2);
	panel2.setSize(320, 400);
	panel2.setPosition(10,200);

	srand(time(0));
}

//--------------------------------------------------------------
void ofApp::update(){
	int x = sizex.get();
	int y = sizey.get();

	if (model.width != x || model.height != y) {
		model.flagstartmodel = false;
		model.width = x;
		model.height = y;
		model.NumberOfCases = 0;
		model.countOfChild = 0;
		model.countOfAdult = 0;
		model.countOfElderly = 0;

		for (int i = 0; i < x; i++) {
			for (int j = 0; j < y; j++) {
				int a = rand() % 5;
				if (a == 0) {
					model.arr[i][j] = new child;
					model.arr[i][j]->setstatus(3);
					model.countOfChild += 1;
				}
				if (a == 1 || a == 2 || a == 3) {
					model.arr[i][j] = new adult;
					model.arr[i][j]->setstatus(3);
					model.countOfAdult += 1;
				}
				if (a == 4) {
					model.arr[i][j] = new elderly;
					model.arr[i][j]->setstatus(3);
					model.countOfElderly += 1;
				}
				model.arr[i][j]->setcontacts(contact.get());
				model.arr[i][j]->setrisk(transmission.get());
				model.arr[i][j]->setTravel_radius(radius.get());
				//if (model.width <= 51 && model.height <= 31) 
				model.arr[i][j]->button.setpos(350 + i * 30, 50 + j * 30, 25, 25);
				//else model.arr[i][j]->button.setpos(350 + i * 17, 50 + j * 17, 15, 15);
			}
		}

		generatevaccination();
		generatemask();
		generatecarrier();
		generatesickday();
		generatechronosick();
	}

	model.hospitalcapacity = hospital.get() * model.height * model.width / 100;
	model.chronomortality = chronomortality.get();
	model.vaccinaEfficacy = vaccineEfficacy.get();

	if (model.vaccination != vaccination.get() && model.flagstartmodel == false)generatevaccination();
	if (model.mask != mask.get() && model.flagstartmodel == false)generatemask();
	if (model.carrier != carrier.get() && model.flagstartmodel == false)generatecarrier();
	if (model.sickday != sickday.get() && model.flagstartmodel == false)generatesickday();
	if (model.chronosick != chrosick.get() && model.flagstartmodel == false)generatechronosick();

	if (bstartButton) 
	{ 
		model.step();
		Sleep(40);
		if (model.NumberOfCases <= 0)bstartButton = false;
	}
}

//--------------------------------------------------------------
void ofApp::draw() {
	ofSetColor(ofColor::black);
	ofRect(resetButton);

	if (bstepButton)
	{
		bstepButton = false;
		Sleep(25);
		ofSetColor(ofColor::green);
	}
	else
	{
		ofSetColor(ofColor::black);
	}
	ofRect(stepButton);

	if (bstartButton)
	{
		ofSetColor(ofColor::green);
	}
	else
	{
		ofSetColor(ofColor::black);
	}
	ofRect(startButton);

	ofSetColor(ofColor::white);

	ofDrawBitmapString("Step", 550, 30);
	ofDrawBitmapString("Reset", 420, 30);

	ofDrawBitmapString("Healthy people", 50, 435);
	ofDrawBitmapString("Dead", 50, 475);
	ofDrawBitmapString("Vaccinated people", 50, 515);
	ofDrawBitmapString("Incubation period", 50, 555);
	ofDrawBitmapString("The period of symptoms", 50, 595);
	ofDrawBitmapString("Adult on a sickday", 50, 635);
	ofDrawBitmapString("Children are immune to the disease", 50, 675);
	ofDrawBitmapString("Recovered", 50, 715);



	ofSetColor(ofColor::black);
	ofRect(black);
	ofSetColor(ofColor::gray);
	ofRect(gray);
	ofSetColor(ofColor::blue);
	ofRect(blue);
	ofSetColor(ofColor::red);
	ofRect(red);
	ofSetColor(ofColor::lightPink);
	ofRect(pink);
	ofSetColor(ofColor::gold);
	ofRect(gold);
	ofSetColor(ofColor::white);
	ofRect(white);
	ofSetColor(ofColor::lightGreen);
	ofRect(green);

	panel.draw();
	panel2.draw();
	
	for (int i = 0; i < model.width; i++) {
		for (int j = 0; j < model.height; j++) {
			model.arr[i][j]->setcontacts(contact.get());
			model.arr[i][j]->setrisk(transmission.get());
			model.arr[i][j]->setTravel_radius(radius.get());
			model.arr[i][j]->setincubation(incubation.get());
			model.arr[i][j]->setperiodOfIllness(periodOfIllness.get());
			model.arr[i][j]->setfatal(mortality.get());


			if (model.arr[i][j]->getstatus() == -1) {
				ofSetColor(ofColor::black);
			}
			else if (model.arr[i][j]->getstatus() == 0) {
				ofSetColor(ofColor::gray);
			}
			else if (model.arr[i][j]->getstatus() == 1) {
				if (adult* obj = dynamic_cast<adult*>(model.arr[i][j]))
				{
					if (obj->checksickday() == true)
					{
						ofSetColor(ofColor::blue);
					}
					else ofSetColor(ofColor::red);
				}
				else ofSetColor(ofColor::red);
			}
			else if (model.arr[i][j]->getstatus() == 2) {
				ofSetColor(ofColor::lightPink);
			}
			else if (model.arr[i][j]->getstatus() == 3) {
				ofSetColor(ofColor::white);
				if (model.arr[i][j]->getvaccination() == true) ofSetColor(ofColor::gold);
				if (child* obj = dynamic_cast<child*>(model.arr[i][j])) 
				{
					if (obj->checkcarrier() == false)
					{
						ofSetColor(ofColor::lightGreen);
					};
				}
			}
			ofRect(model.arr[i][j]->button.rectButton);
		}
	}

}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == 'r') {
		model.width = -1;
		model.height = -1;
		bstartButton = false;
		model.flagstartmodel = false;
	 }
	else if (key == 's' && model.NumberOfCases != 0) {
		bstartButton = !bstartButton;
		model.flagstartmodel = true;
	}
	else if (key == 'd' && model.NumberOfCases != 0) {
		bstartButton = false;
		model.flagstartmodel = true;
		bstepButton = true;
		model.step();
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------

void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	for (int i = 0; i < model.width; i++) {
		for (int j = 0; j < model.height; j++) {
			if (model.arr[i][j]->button.mousePressed(x, y)) {
				if (1) {
					if (model.arr[i][j]->getstatus() == 1)
					{
						model.NumberOfCases -= 1;
						model.NumberOfPatients -= 1;
						model.arr[i][j]->setstatus(3);
						break;
					}
					if (model.arr[i][j]->getstatus() == 2)
					{
						model.NumberOfPatients += 1;
						model.arr[i][j]->setstatus(1);
						break;
					}
					if (child* obj = dynamic_cast<child*>(model.arr[i][j]))
					{
						if (obj->checkcarrier() == true && obj->getstatus() == 3)
						{
							model.NumberOfCases += 1;
							//model.NumberOfPatients += 1;
							model.arr[i][j]->setstatus(2);
							model.arr[i][j]->sethealth(0);

						};
					}
					else if (adult* obj = dynamic_cast<adult*>(model.arr[i][j]))
					{
						if (obj->getstatus() == 3)
						{
							model.NumberOfCases += 1;
							//model.NumberOfPatients += 1;
							model.arr[i][j]->setstatus(2);
							model.arr[i][j]->sethealth(0);

						};
					}
					else if (elderly* obj = dynamic_cast<elderly*>(model.arr[i][j]))
					{
						if (obj->getstatus() == 3)
						{
							model.NumberOfCases += 1;
							//model.NumberOfPatients += 1;
							model.arr[i][j]->setstatus(2);
							model.arr[i][j]->sethealth(0);

						};
					}
				}
			}
		}
	}

	if (resetButton.inside(x, y)) {
		model.width = -1;
		model.height = -1;
		bstartButton = false;
		model.flagstartmodel = false;
	}
	else if (stepButton.inside(x, y) && model.NumberOfCases != 0) {
		bstartButton = false;
		model.flagstartmodel = true;
		bstepButton = true;
		model.step();
	}
	else if (startButton.inside(x, y) && model.NumberOfCases != 0) {
		bstartButton = !bstartButton;
		model.flagstartmodel = true;
	}
}
//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}


void ofApp::generatevaccination()
{
	int temp = vaccination.get() * model.width * model.height / 100;
	for (int i = 0; i < model.width; i++) for (int j = 0; j < model.height; j++) { model.arr[i][j]->setvaccination(false); model.arr[i][j]->setstatus(3); }
	while(temp){
		for (int i = 0; i < model.width; i++) {
			for (int j = 0; j < model.height; j++) {
				if (random(1) && model.arr[i][j]->getvaccination() == false && temp > 0)
				{
					model.arr[i][j]->setvaccination(true);
					temp--;
				}
			}
		}
	}
	model.vaccination = vaccination.get();
}


void ofApp::generatemask() 
{
	int temp = mask.get() * model.width * model.height / 100;
	for (int i = 0; i < model.width; i++) for (int j = 0; j < model.height; j++) { model.arr[i][j]->setmask(false); }
	while (temp) {
		for (int i = 0; i < model.width; i++) {
			for (int j = 0; j < model.height; j++) {
				if (random(1) && model.arr[i][j]->getmask() == false && temp > 0)
				{
					model.arr[i][j]->setmask(true);
					temp--;
				}
			}
		}
	}
	model.mask = mask.get();
}

void ofApp::generatecarrier() 
{
	int temp = carrier.get() * model.countOfChild / 100;
	for (int i = 0; i < model.width; i++) for (int j = 0; j < model.height; j++) 
	{
		if (child* obj = dynamic_cast<child*>(model.arr[i][j])) { obj->setcarrier(false); model.arr[i][j]->setstatus(3); }
	}
	while (temp) {
		for (int i = 0; i < model.width; i++) {
			for (int j = 0; j < model.height; j++) {
				if (child* obj = dynamic_cast<child*>(model.arr[i][j]) )
					if (random(2) && obj->checkcarrier() == false && temp > 0)
					{
						obj->setcarrier(true);
						temp--;
					}
			}
		}
	}
	model.carrier = carrier.get();
}

void ofApp::generatesickday()
{
	int temp = sickday.get() * model.countOfAdult / 100;
	for (int i = 0; i < model.width; i++) for (int j = 0; j < model.height; j++)
	{
		if (adult* obj = dynamic_cast<adult*>(model.arr[i][j]))obj->setsickday(false);
	}
	while (temp) {
		for (int i = 0; i < model.width; i++) {
			for (int j = 0; j < model.height; j++) {
				if (adult* obj = dynamic_cast<adult*>(model.arr[i][j]))
					if (random(2) && obj->checksickday() == false && temp > 0)
					{
						obj->setsickday(true);
						temp--;
					}
			}
		}
	}
	model.sickday = sickday.get();
}

void ofApp::generatechronosick()
{
	int temp = chrosick.get() * model.countOfElderly / 100;
	for (int i = 0; i < model.width; i++) for (int j = 0; j < model.height; j++)
	{
		if (elderly* obj = dynamic_cast<elderly*>(model.arr[i][j]))obj->setchronicdiseases(false);
	}
	while (temp) {
		for (int i = 0; i < model.width; i++) {
			for (int j = 0; j < model.height; j++) {
				if (elderly* obj = dynamic_cast<elderly*>(model.arr[i][j]))
					if (random(2) && obj->checkchronicdiseases() == false && temp > 0)
					{
						obj->setchronicdiseases(true);
						temp--;
					}
			}
		}
	}
	model.chronosick = chrosick.get();
}

