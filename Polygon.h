#pragma once
#include "Tool.h"

class PolygonTool :
	public Tool
{
public:
	PolygonTool();
	void MouseLButtonDown(int, int);
	void MouseMove(int, int);
	void MouseLButtonUp(int, int);
	void MouseRButtonUp(int, int);
private:
	int start_x;
	int start_y;
	
	void StopPainting();
};

