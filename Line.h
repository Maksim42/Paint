#pragma once

#include "Tool.h"

class Line :
	public Tool
{
public:
	Line();
	void MouseLButtonDown(int, int);
	void MouseMove(int, int);
	void MouseLButtonUp(int, int);
};

