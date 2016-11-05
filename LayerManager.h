#pragma once
#include "Layer.h"
#include "MetafileLayer.h"
#include "Lens.h"

#define NUM_LAYERS 2

class LayerManager { 
public:
	static LayerManager	   *instance;
	HWND					hWin;
	RECT					client_area;

	static void				Init(HWND);
	Layer				   *GetLayer(int);
	MetafileLayer		   *GetMetafile();
	HDC						GetWinDc();
	void					SetAllPensColor(COLORREF);
	void					SetAllBrushColor(COLORREF);
	void					SetAllPensWidth(int);
	void					Clear();
	void					DrawingImage(LPCTSTR);
private:
	Layer				   *layer[NUM_LAYERS];
	MetafileLayer		   *metafile;
	HDC						winDC;

							LayerManager(HWND);
};