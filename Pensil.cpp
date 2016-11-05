#include "stdafx.h"
#include "Pensil.h"

Pensil::Pensil(): Tool() {
}

void Pensil::MouseLButtonDown(int x, int y) {
	POINT cordinate = Lens::instance->CalculationRealCordinate(x, y);
	isPaint = true;

	MoveToEx(LayerManager::instance->GetLayer(0)->dc, cordinate.x, cordinate.y, NULL);
	MoveToEx(LayerManager::instance->GetLayer(1)->dc, cordinate.x, cordinate.y, NULL);
	MoveToEx(LayerManager::instance->GetMetafile()->dc, cordinate.x, cordinate.y, NULL);
}

void Pensil::MouseMove(int x, int y) {
	if (isPaint) {
		POINT cordinate = Lens::instance->CalculationRealCordinate(x, y);

		LineTo(LayerManager::instance->GetLayer(0)->dc, cordinate.x, cordinate.y);
		LineTo(LayerManager::instance->GetMetafile()->dc, cordinate.x, cordinate.y);


		BitBlt(LayerManager::instance->GetLayer(1)->dc, 0, 0, LayerManager::instance->client_area.right,
			LayerManager::instance->client_area.bottom, LayerManager::instance->GetLayer(0)->dc, 0, 0, SRCCOPY);

		InvalidateRect(LayerManager::instance->hWin, &(LayerManager::instance->client_area), false);
		TrackMouseEvent(&trackMouseEvent);
	}
}

void Pensil::MouseLButtonUp(int x, int y) {
	isPaint = false;
}
