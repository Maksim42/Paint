#pragma once

#include "Tool.h"

class Pensil : public Tool {
public:
	Pensil();
	void MouseLButtonDown(int, int);
	void MouseMove(int, int);
	void MouseLButtonUp(int, int);
};

