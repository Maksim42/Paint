#include "stdafx.h"
#include "Layers.h"

Layers::Layers(HWND hWin) {
	this->hWin = hWin;
	winDC = GetDC(hWin);
	brush = CreateSolidBrush(RGB(255, 255, 255));

	GetClientRect(hWin, &clientArea);
	main = GetLayer();
	temporari = GetLayer();
	scale = GetLayer();
}

HDC Layers::GetLayer() {
	HDC layer = CreateCompatibleDC(winDC);

	HBITMAP BitMp = CreateCompatibleBitmap(winDC, clientArea.right, clientArea.bottom);
	ChangeObject(layer, BitMp);

	ChangeObject(layer, brush);
	FillRect(layer, &clientArea, brush);

	return layer;
}

Layers *Layers::instance = NULL;

void Layers::Init(HWND hWin) {
	instance = new Layers(hWin);
}

