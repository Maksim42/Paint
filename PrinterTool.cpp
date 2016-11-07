#include "stdafx.h"
#include "PrinterTool.h"

PrinterTool::PrinterTool() : Tool() {
}

void PrinterTool::MouseLButtonDown(int x, int y) {
	isPaint = true;
	_x = x;
	_y = y;

	PenProp new_pen;
	new_pen.color = BLACKNESS;
	new_pen.style = PS_DASH;
	new_pen.width = 1;
	old_pen = LayerManager::instance->GetLayer(1)->SetPen(new_pen);

	LayerManager::instance->GetLayer(1)->BrushOff();
}

void PrinterTool::MouseMove(int x, int y) {
	if (isPaint) {
		BitBlt(LayerManager::instance->GetLayer(1)->dc, 0, 0, LayerManager::instance->client_area.right,
			LayerManager::instance->client_area.bottom, LayerManager::instance->GetLayer(0)->dc, 0, 0, SRCCOPY);

		Rectangle(LayerManager::instance->GetLayer(1)->dc, _x, _y, x, y);

		InvalidateRect(LayerManager::instance->hWin, &(LayerManager::instance->client_area), false);
		TrackMouseEvent(&trackMouseEvent);
	}
}

void PrinterTool::MouseLButtonUp(int x, int y) {
	isPaint = false;
	LayerManager::instance->GetLayer(1)->SetPen(old_pen);
	LayerManager::instance->GetLayer(1)->BrushOn();

	BitBlt(LayerManager::instance->GetLayer(1)->dc, 0, 0, LayerManager::instance->client_area.right,
		LayerManager::instance->client_area.bottom, LayerManager::instance->GetLayer(0)->dc, 0, 0, SRCCOPY);

	InvalidateRect(LayerManager::instance->hWin, &(LayerManager::instance->client_area), false);

	Printer::instance->Print(_x, _y, x, y);
}

void PrinterTool::StopPainting() {
	if (isPaint) {
		isPaint = false;
		LayerManager::instance->GetLayer(1)->SetPen(old_pen);
		LayerManager::instance->GetLayer(1)->BrushOn();

		BitBlt(LayerManager::instance->GetLayer(1)->dc, 0, 0, LayerManager::instance->client_area.right,
			LayerManager::instance->client_area.bottom, LayerManager::instance->GetLayer(0)->dc, 0, 0, SRCCOPY);

		InvalidateRect(LayerManager::instance->hWin, &(LayerManager::instance->client_area), false);
	}
}

