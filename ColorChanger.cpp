#include "stdafx.h"
#include "ColorChanger.h"

ColorChanger *ColorChanger::instance = NULL;

ColorChanger::ColorChanger(HWND hWnd) {
	unsigned int structSize = sizeof(CHOOSECOLOR);

	ZeroMemory(&dialog, structSize);
	dialog.lStructSize = structSize;
	dialog.hwndOwner = hWnd;
	dialog.lpCustColors = custColor;
	dialog.Flags = CC_RGBINIT | CC_FULLOPEN;
	dialog.rgbResult = RGB(0x80, 0x80, 0x80);
}

void ColorChanger::Init(HWND hWnd) {
	if (ColorChanger::instance == NULL) {
		ColorChanger::instance = new ColorChanger(hWnd);
	}
}

void ColorChanger::ChangePen() {
	if (ChooseColor(&dialog)) {
		LayerManager::instance->SetAllPensColor(dialog.rgbResult);
	}
}

void ColorChanger::ChangeBrush() {
	if (ChooseColor(&dialog)) {
		LayerManager::instance->SetAllBrushColor(dialog.rgbResult);
	}
}


