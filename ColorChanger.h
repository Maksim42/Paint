#pragma once

#include "LayerManager.h"
#include <CommDlg.h>

class ColorChanger
{
public:
	static ColorChanger  *instance;
	
	static void Init(HWND);
	void ChangePen();
	void ChangeBrush();
private:
	ColorChanger(HWND);

	CHOOSECOLOR dialog;
	COLORREF custColor[16];
};

