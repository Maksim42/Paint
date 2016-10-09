#include "stdafx.h"
#include "Pensil.h"

Pensil::Pensil(): Tool() {
}

void Pensil::MouseLButtonDown(int x, int y) {
	isPaint = true;

	MoveToEx(Layers::instance->main, x, y, NULL);
	MoveToEx(Layers::instance->temporari, x, y, NULL);
}

void Pensil::MouseMove(int x, int y) {
	if (isPaint) {
		LineTo(Layers::instance->main, x, y);

		BitBlt(Layers::instance->temporari, 0, 0, Layers::instance->clientArea.right,
			Layers::instance->clientArea.bottom, Layers::instance->main, 0, 0, SRCCOPY);


		InvalidateRect(Layers::instance->hWin, &(Layers::instance->clientArea), false);
		TrackMouseEvent(&trackMouseEvent);
	}
}

void Pensil::MouseLButtonUp(int x, int y) {
	isPaint = false;
}
