#include "stdafx.h"
#include "Polylines.h"


Polylines::Polylines() {
}

void Polylines::MouseLButtonDown(int x, int y) {
	POINT cordinate = Lens::instance->CalculationRealCordinate(x, y);

	if (!isPaint) {
		isPaint = true;
		_x = cordinate.x;
		_y = cordinate.y;
	}
}

void Polylines::MouseMove(int x, int y) {
	if (isPaint) {
		POINT cordinate = Lens::instance->CalculationRealCordinate(x, y);

		BitBlt(LayerManager::instance->GetLayer(1)->dc, 0, 0, LayerManager::instance->client_area.right,
			LayerManager::instance->client_area.bottom, LayerManager::instance->GetLayer(0)->dc, 0, 0, SRCCOPY);

		MoveToEx(LayerManager::instance->GetLayer(1)->dc, _x, _y, NULL);
		LineTo(LayerManager::instance->GetLayer(1)->dc, cordinate.x, cordinate.y);

		InvalidateRect(LayerManager::instance->hWin, &(LayerManager::instance->client_area), false);
		TrackMouseEvent(&trackMouseEvent);
	}
}

void Polylines::MouseLButtonUp(int x, int y) {
	if (isPaint) {
		POINT cordinate = Lens::instance->CalculationRealCordinate(x, y);

		BitBlt(LayerManager::instance->GetLayer(1)->dc, 0, 0, LayerManager::instance->client_area.right,
			LayerManager::instance->client_area.bottom, LayerManager::instance->GetLayer(0)->dc, 0, 0, SRCCOPY);

		MoveToEx(LayerManager::instance->GetLayer(0)->dc, _x, _y, NULL);
		LineTo(LayerManager::instance->GetLayer(0)->dc, cordinate.x, cordinate.y);
		MoveToEx(LayerManager::instance->GetMetafile()->dc, _x, _y, NULL);
		LineTo(LayerManager::instance->GetMetafile()->dc, cordinate.x, cordinate.y);

		_x = cordinate.x;
		_y = cordinate.y;

		InvalidateRect(LayerManager::instance->hWin, &(LayerManager::instance->client_area), false);
	}
}

void Polylines::MouseRButtonUp(int x, int y) {
	if (isPaint) {
		isPaint = false;

		BitBlt(LayerManager::instance->GetLayer(1)->dc, 0, 0, LayerManager::instance->client_area.right,
			LayerManager::instance->client_area.bottom, LayerManager::instance->GetLayer(0)->dc, 0, 0, SRCCOPY);

		InvalidateRect(LayerManager::instance->hWin, &(LayerManager::instance->client_area), false);
	}
}
