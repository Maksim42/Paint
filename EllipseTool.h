#pragma once
#include "Tool.h"
class EllipseTool :
	public Tool
{
public:
	EllipseTool();
	void MouseLButtonDown(int, int);
	void MouseMove(int, int);
	void MouseLButtonUp(int, int);
};

