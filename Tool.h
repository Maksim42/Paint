#pragma once

#include "Layers.h"

class Tool {
public:
	Tool();
	virtual void MouseLButtonDown(int, int);
	virtual void MouseMove(int, int);
	virtual void MouseLButtonUp(int, int);
protected:
	bool isPaint;
	int	_x;
	int	_y;
};

