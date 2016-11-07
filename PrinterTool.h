#pragma once
#include "Tool.h"
#include "Printer.h"

class PrinterTool : public Tool {
public:
	PenProp old_pen;

	PrinterTool();
	void MouseLButtonDown(int, int);
	void MouseMove(int, int);
	void MouseLButtonUp(int, int);
	void StopPainting();
};

