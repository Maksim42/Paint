#include "stdafx.h"
#include "Tool.h"

Tool::Tool() {
	isPaint = false;
	trackMouseEvent.cbSize = sizeof(trackMouseEvent);
	trackMouseEvent.dwFlags = TME_LEAVE; //отслеживаем выход курсора
	trackMouseEvent.hwndTrack = Layers::instance->hWin; //из этого окна
}

void Tool::StopPainting() {
	isPaint = false;

	BitBlt(Layers::instance->temporari, 0, 0, Layers::instance->clientArea.right,
		Layers::instance->clientArea.bottom, Layers::instance->main, 0, 0, SRCCOPY);

	InvalidateRect(Layers::instance->hWin, &(Layers::instance->clientArea), false);
}
