#include "stdafx.h"
#include "EllipseTool.h"


EllipseTool::EllipseTool()
{
}


void EllipseTool::MouseLButtonDown(int x, int y) {
	POINT cordinate = Lens::instance->CalculationRealCordinate(x, y);
	isPaint = true;
	_x = cordinate.x;
	_y = cordinate.y;
}

void EllipseTool::MouseMove(int x, int y) {
	if (isPaint) {
		POINT cordinate = Lens::instance->CalculationRealCordinate(x, y);

		BitBlt(LayerManager::instance->GetLayer(1)->dc, 0, 0, LayerManager::instance->client_area.right,
			LayerManager::instance->client_area.bottom, LayerManager::instance->GetLayer(0)->dc, 0, 0, SRCCOPY);

		Ellipse(LayerManager::instance->GetLayer(1)->dc, _x, _y, cordinate.x, cordinate.y);

		InvalidateRect(LayerManager::instance->hWin, &(LayerManager::instance->client_area), false);
		TrackMouseEvent(&trackMouseEvent);
	}
}

void EllipseTool::MouseLButtonUp(int x, int y) {
	if (isPaint) {
		POINT cordinate = Lens::instance->CalculationRealCordinate(x, y);
		isPaint = false;

		Ellipse(LayerManager::instance->GetLayer(0)->dc, _x, _y, cordinate.x, cordinate.y);
		Ellipse(LayerManager::instance->GetMetafile()->dc, _x, _y, cordinate.x, cordinate.y);

		InvalidateRect(LayerManager::instance->hWin, &(LayerManager::instance->client_area), false);
	}
}