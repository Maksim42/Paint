#include "stdafx.h"
#include "Line.h"


Line::Line(): Tool() {
}

void Line::MouseLButtonDown(int x, int y) {
	isPaint = true;
	POINT real_cordinate = Lens::instance->CalculationRealCordinate(x, y);
	_x = real_cordinate.x;
	_y = real_cordinate.y;

	MoveToEx(LayerManager::instance->GetLayer(0)->dc, real_cordinate.x, real_cordinate.y, NULL);
	MoveToEx(LayerManager::instance->GetLayer(1)->dc, real_cordinate.x, real_cordinate.y, NULL);
	MoveToEx(LayerManager::instance->GetMetafile()->dc, real_cordinate.x, real_cordinate.y, NULL);
}

void Line::MouseMove(int x, int y) {
	if (isPaint) {
		POINT real_cordinate = Lens::instance->CalculationRealCordinate(x, y);

		BitBlt(LayerManager::instance->GetLayer(1)->dc, 0, 0, LayerManager::instance->client_area.right,
			LayerManager::instance->client_area.bottom, LayerManager::instance->GetLayer(0)->dc, 0, 0, SRCCOPY);

		MoveToEx(LayerManager::instance->GetLayer(1)->dc, _x, _y, NULL);
		LineTo(LayerManager::instance->GetLayer(1)->dc, real_cordinate.x, real_cordinate.y);

		InvalidateRect(LayerManager::instance->hWin, &(LayerManager::instance->client_area), false);
		TrackMouseEvent(&trackMouseEvent);
	}
}

void Line::MouseLButtonUp(int x, int y) {
	if (isPaint) {
		isPaint = false;
		POINT real_cordinate = Lens::instance->CalculationRealCordinate(x, y);

		LineTo(LayerManager::instance->GetLayer(0)->dc, real_cordinate.x, real_cordinate.y);
		LineTo(LayerManager::instance->GetMetafile()->dc, real_cordinate.x, real_cordinate.y);

		InvalidateRect(LayerManager::instance->hWin, &(LayerManager::instance->client_area), false);
	}
}
