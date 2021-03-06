#pragma once

#include "LayerManager.h"
#include "Lens.h"

class Tool {
public:
	Tool();
	virtual void MouseLButtonDown(int, int) = 0;
	virtual void MouseMove(int, int) = 0;
	virtual void MouseLButtonUp(int, int) = 0;
	virtual void MouseRButtonUp(int, int);
	virtual void StopPainting();
protected:
	bool isPaint;
	int	_x;
	int	_y;
	TRACKMOUSEEVENT trackMouseEvent;
};

