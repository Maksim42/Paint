#pragma once
#include "Tool.h"

class Polylines :
	public Tool
{
public:
	Polylines();
	void MouseLButtonDown(int, int);
	void MouseMove(int, int);
	void MouseLButtonUp(int, int);
	void MouseRButtonUp(int, int);
};

