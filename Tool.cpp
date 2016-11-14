#include "stdafx.h"
#include "Tool.h"

Tool::Tool() {
	isPaint = false;
	trackMouseEvent.cbSize = sizeof(trackMouseEvent);
	trackMouseEvent.dwFlags = TME_LEAVE;
	trackMouseEvent.hwndTrack = LayerManager::instance->hWin;
}

void Tool::MouseRButtonUp(int, int) {
}

void Tool::StopPainting() {
	if (isPaint) {
		isPaint = false;

		BitBlt(LayerManager::instance->GetLayer(1)->dc, 0, 0, LayerManager::instance->client_area.right,
			LayerManager::instance->client_area.bottom, LayerManager::instance->GetLayer(0)->dc, 0, 0, SRCCOPY);

		InvalidateRect(LayerManager::instance->hWin, &(LayerManager::instance->client_area), false);
	}
}
