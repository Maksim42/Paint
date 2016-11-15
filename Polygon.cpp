#include "stdafx.h"
#include "Polygon.h"


PolygonTool::PolygonTool(){
}

void PolygonTool::MouseLButtonDown(int x, int y) {
	POINT cordinate = Lens::instance->CalculationRealCordinate(x, y);

	if (!isPaint) {
		isPaint = true;
		_x = cordinate.x;
		_y = cordinate.y;
		start_x = cordinate.x;
		start_y = cordinate.y;
	}
}

void PolygonTool::MouseMove(int x, int y) {
	if (isPaint) {
		POINT cordinate = Lens::instance->CalculationRealCordinate(x, y);

		BitBlt(LayerManager::instance->GetLayer(1)->dc, 0, 0, LayerManager::instance->client_area.right,
			LayerManager::instance->client_area.bottom, LayerManager::instance->GetLayer(0)->dc, 0, 0, SRCCOPY);

		MoveToEx(LayerManager::instance->GetLayer(1)->dc, _x, _y, NULL);
		LineTo(LayerManager::instance->GetLayer(1)->dc, cordinate.x, cordinate.y);
		LineTo(LayerManager::instance->GetLayer(1)->dc, start_x, start_y);

		InvalidateRect(LayerManager::instance->hWin, &(LayerManager::instance->client_area), false);
		TrackMouseEvent(&trackMouseEvent);
	}
}

void PolygonTool::MouseLButtonUp(int x, int y) {
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

void PolygonTool::MouseRButtonUp(int x, int y) {
	if (isPaint) {
		isPaint = false;

		MoveToEx(LayerManager::instance->GetLayer(0)->dc, start_x, start_y, NULL);
		LineTo(LayerManager::instance->GetLayer(0)->dc, _x, _y);
		MoveToEx(LayerManager::instance->GetMetafile()->dc, start_x, start_y, NULL);
		LineTo(LayerManager::instance->GetMetafile()->dc, _x, _y);

		BitBlt(LayerManager::instance->GetLayer(1)->dc, 0, 0, LayerManager::instance->client_area.right,
			LayerManager::instance->client_area.bottom, LayerManager::instance->GetLayer(0)->dc, 0, 0, SRCCOPY);

		InvalidateRect(LayerManager::instance->hWin, &(LayerManager::instance->client_area), false);
	}
}

void PolygonTool::StopPainting() {
	if (isPaint) {
		isPaint = false;

		MoveToEx(LayerManager::instance->GetLayer(0)->dc, start_x, start_y, NULL);
		LineTo(LayerManager::instance->GetLayer(0)->dc, _x, _y);
		MoveToEx(LayerManager::instance->GetMetafile()->dc, start_x, start_y, NULL);
		LineTo(LayerManager::instance->GetMetafile()->dc, _x, _y);

		BitBlt(LayerManager::instance->GetLayer(1)->dc, 0, 0, LayerManager::instance->client_area.right,
			LayerManager::instance->client_area.bottom, LayerManager::instance->GetLayer(0)->dc, 0, 0, SRCCOPY);

		InvalidateRect(LayerManager::instance->hWin, &(LayerManager::instance->client_area), false);
	}
}