#include "stdafx.h"
#include "Line.h"


Line::Line(): Tool() {
}

void Line::MouseLButtonDown(int x, int y) {
	isPaint = true;
	_x = x;
	_y = y;

	MoveToEx(Layers::instance->main, x, y, NULL);
	MoveToEx(Layers::instance->temporari, x, y, NULL);
}

void Line::MouseMove(int x, int y) {
	if (isPaint) {
		BitBlt(Layers::instance->temporari, 0, 0, Layers::instance->clientArea.right,
			Layers::instance->clientArea.bottom, Layers::instance->main, 0, 0, SRCCOPY);

		MoveToEx(Layers::instance->temporari, _x, _y, NULL);
		LineTo(Layers::instance->temporari, x, y);

		InvalidateRect(Layers::instance->hWin, &(Layers::instance->clientArea), false);
		TrackMouseEvent(&trackMouseEvent);
	}
}

void Line::MouseLButtonUp(int x, int y) {
	if (isPaint) {
		isPaint = false;

		LineTo(Layers::instance->main, x, y);

		InvalidateRect(Layers::instance->hWin, &(Layers::instance->clientArea), false);
	}
}
