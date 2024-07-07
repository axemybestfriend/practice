#include "cell.h"

cell::cell(int x, int y, int w, int h)
{
	this->bRectButton = false;
	this->rectButton.set(x, y, w, h);
	ofRect(rectButton);
}

cell::cell()
{
	this->bRectButton = false;
}

void cell::setpos(int x, int y, int w, int h)
{
	this->rectButton.set(x, y, w, h);
}

bool cell::mousePressed(int x ,int y)
{
	if (this->rectButton.inside(x, y))return true;
	
	return false;
}
