#pragma once

#include "LayerManager.h"

class Tool {
public:
	Tool();
	virtual void MouseLButtonDown(int, int) = 0;
	virtual void MouseMove(int, int) = 0;
	virtual void MouseLButtonUp(int, int) = 0;
	virtual void StopPainting();
protected:
	bool isPaint;
	int	_x;
	int	_y;
	TRACKMOUSEEVENT trackMouseEvent;
};

