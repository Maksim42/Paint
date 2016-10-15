#include "stdafx.h"
#include "Pensil.h"

Pensil::Pensil(): Tool() {
}

void Pensil::MouseLButtonDown(int x, int y) {
	isPaint = true;

	MoveToEx(LayerManager::instance->GetLayer(0)->dc, x, y, NULL);
	MoveToEx(LayerManager::instance->GetLayer(1)->dc, x, y, NULL);
}

void Pensil::MouseMove(int x, int y) {
	if (isPaint) {
		LineTo(LayerManager::instance->GetLayer(0)->dc, x, y);

		BitBlt(LayerManager::instance->GetLayer(1)->dc, 0, 0, LayerManager::instance->client_area.right,
			LayerManager::instance->client_area.bottom, LayerManager::instance->GetLayer(0)->dc, 0, 0, SRCCOPY);

		InvalidateRect(LayerManager::instance->hWin, &(LayerManager::instance->client_area), false);
		TrackMouseEvent(&trackMouseEvent);
	}
}

void Pensil::MouseLButtonUp(int x, int y) {
	isPaint = false;
}
