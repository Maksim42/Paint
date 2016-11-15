#pragma once
#include "Tool.h"

class RectangleTool :
	public Tool
{
public:
	RectangleTool();
	void MouseLButtonDown(int, int);
	void MouseMove(int, int);
	void MouseLButtonUp(int, int);
};

