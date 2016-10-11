#include "stdafx.h"
#include "Layers.h"

Layers::Layers(HWND hWin) {
	this->hWin = hWin;
	winDC = GetDC(hWin);
	brush = (HBRUSH)GetStockObject(DC_BRUSH);
	pen = (HPEN)GetStockObject(DC_PEN);

	GetClientRect(hWin, &clientArea);
	main = GetLayer();
	temporari = GetLayer();
	scale = GetLayer();
}

HDC Layers::GetLayer() {
	HDC layer = CreateCompatibleDC(winDC);

	ChangeObject(layer, pen);

	HBITMAP BitMp = CreateCompatibleBitmap(winDC, clientArea.right, clientArea.bottom);
	ChangeObject(layer, BitMp);

	ChangeObject(layer, brush);
	FillRect(layer, &clientArea, brush);

	return layer;
}

Layers *Layers::instance = NULL;

void Layers::Init(HWND hWin) {
	if (Layers::instance == NULL) {
		instance = new Layers(hWin);
	}
}

