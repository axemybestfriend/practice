#pragma once

#include "ofMain.h"
#include "D:\of_v0.12.0_vs_release\apps\myApps\practice\cell.h"
#include "D:\of_v0.12.0_vs_release\apps\myApps\practice\child.h"
#include "D:\of_v0.12.0_vs_release\apps\myApps\practice\adult.h"
#include "D:\of_v0.12.0_vs_release\apps\myApps\practice\elderly.h"
#include "D:\of_v0.12.0_vs_release\apps\myApps\practice\info.h"
#include "D:\of_v0.12.0_vs_release\apps\myApps\practice\info.cpp"

#include "ofxGui.h"



class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);


		ofxPanel panel;
		ofxPanel panel2;

		info model;

		ofParameterGroup sliderGroup;
		ofParameter<int> sizex;
		ofParameter<int> sizey;
		ofParameter<int> radius;
		ofParameter<int> contact;
		ofParameter<int> incubation;
		ofParameter<int> periodOfIllness;
		ofParameter<int> transmission;
		ofParameter<int> mortality;
		ofParameter<int> hospital;


		ofParameterGroup sliderGroup2;
		ofParameter<int> mask;
		ofParameter<int> vaccination;
		ofParameter<int> carrier;
		ofParameter<int> sickday;
		ofParameter<int> chrosick;


		ofParameterGroup sliderGroup3;
		ofParameter<int> chronomortality;
		ofParameter<int> vaccineEfficacy;


		ofRectangle resetButton;
		bool bresetButton;

		ofRectangle startButton;
		bool bstartButton;

		ofRectangle stepButton;
		bool bstepButton;


		ofRectangle black;
		ofRectangle gold;
		ofRectangle pink;
		ofRectangle red;
		ofRectangle blue;
		ofRectangle green;
		ofRectangle white;
		ofRectangle gray;



		void generatevaccination();

		void generatemask();

		void generatecarrier();

		void generatesickday();
		
		void generatechronosick();

		ofTrueTypeFont font;
};
