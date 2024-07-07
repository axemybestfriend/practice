#pragma once

#include "ofxGui.h"

class cell
{
public:
	ofRectangle rectButton;
	bool bRectButton;
	cell(int x, int y, int w,int h);
	cell();
	void setpos(int x, int y, int w, int h);
	bool mousePressed(int x, int y);
	~cell() {}
};

