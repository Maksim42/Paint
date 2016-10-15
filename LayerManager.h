#pragma once
#include "Layer.h"
#define NUM_LAYERS 2

class LayerManager { 
public:
	static LayerManager	   *instance;
	HWND					hWin;
	HDC						winDC;
	RECT					client_area;

	static void				Init(HWND);
	Layer				   *GetLayer(int);
	void					SetAllPensColor(COLORREF);
	void					SetAllBrushColor(COLORREF);
	void					SetAllPensWidth(int);
private:
	Layer				   *layer[NUM_LAYERS];

							LayerManager(HWND);
};