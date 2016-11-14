#include "stdafx.h"
#include "Rectangle.h"


RectangleTool::RectangleTool() : Tool() {
}

void RectangleTool::MouseLButtonDown(int x, int y) {
	POINT cordinate = Lens::instance->CalculationRealCordinate(x, y);
	isPaint = true;
	_x = cordinate.x;
	_y = cordinate.y;
}

void RectangleTool::MouseMove(int x, int y) {
	if (isPaint) {
		POINT cordinate = Lens::instance->CalculationRealCordinate(x, y);

		BitBlt(LayerManager::instance->GetLayer(1)->dc, 0, 0, LayerManager::instance->client_area.right,
			LayerManager::instance->client_area.bottom, LayerManager::instance->GetLayer(0)->dc, 0, 0, SRCCOPY);

		Rectangle(LayerManager::instance->GetLayer(1)->dc, _x, _y, cordinate.x, cordinate.y);

		InvalidateRect(LayerManager::instance->hWin, &(LayerManager::instance->client_area), false);
		TrackMouseEvent(&trackMouseEvent);
	}
}

void RectangleTool::MouseLButtonUp(int x, int y) {
	POINT cordinate = Lens::instance->CalculationRealCordinate(x, y);

	if (isPaint) {
		isPaint = false;

		Rectangle(LayerManager::instance->GetLayer(0)->dc, _x, _y, cordinate.x, cordinate.y);
		Rectangle(LayerManager::instance->GetMetafile()->dc, _x, _y, cordinate.x, cordinate.y);

		InvalidateRect(LayerManager::instance->hWin, &(LayerManager::instance->client_area), false);
	}
}
