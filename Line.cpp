#include "stdafx.h"
#include "Line.h"


Line::Line(): Tool() {
}

void Line::MouseLButtonDown(int x, int y) {
	isPaint = true;
	_x = x;
	_y = y;

	MoveToEx(LayerManager::instance->GetLayer(0)->dc, x, y, NULL);
	MoveToEx(LayerManager::instance->GetLayer(1)->dc, x, y, NULL);
}

void Line::MouseMove(int x, int y) {
	if (isPaint) {
		BitBlt(LayerManager::instance->GetLayer(1)->dc, 0, 0, LayerManager::instance->client_area.right,
			LayerManager::instance->client_area.bottom, LayerManager::instance->GetLayer(0)->dc, 0, 0, SRCCOPY);

		MoveToEx(LayerManager::instance->GetLayer(1)->dc, _x, _y, NULL);
		LineTo(LayerManager::instance->GetLayer(1)->dc, x, y);

		InvalidateRect(LayerManager::instance->hWin, &(LayerManager::instance->client_area), false);
		TrackMouseEvent(&trackMouseEvent);
	}
}

void Line::MouseLButtonUp(int x, int y) {
	if (isPaint) {
		isPaint = false;

		LineTo(LayerManager::instance->GetLayer(0)->dc, x, y);

		InvalidateRect(LayerManager::instance->hWin, &(LayerManager::instance->client_area), false);
	}
}
