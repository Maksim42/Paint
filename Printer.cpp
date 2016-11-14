#include "stdafx.h"
#include "Printer.h"

Printer *Printer::instance = NULL;

void Printer::Init(HWND hWnd) {
	if (instance == NULL) {
		instance = new Printer(hWnd);
	}
}

Printer::Printer(HWND hWnd) {
	ZeroMemory(&dialog, sizeof(dialog));
	dialog.lStructSize = sizeof(dialog);
	dialog.hwndOwner = hWnd;
	dialog.hDevMode = NULL; // Не забудьте освободить или сохранить hDevMode
	dialog.hDevNames = NULL; // Не забудьте освободить или сохранить hDevNames
	dialog.Flags = PD_USEDEVMODECOPIESANDCOLLATE | PD_RETURNDC;
	dialog.nCopies = 1;
	dialog.nFromPage = 0xFFFF;
	dialog.nToPage = 0xFFFF;
	dialog.nMinPage = 1;
	dialog.nMaxPage = 0xFFFF;

	info.cbSize = sizeof(DOCINFO);
	info.lpszDocName = L"Print Picture";
	info.fwType = NULL;
	info.lpszDatatype = NULL;
	info.lpszOutput = NULL;
}

Printer::~Printer() {
}

void Printer::Print(int x, int y, int x1, int y1) {
	int temp;

	if (x1 < x) {
		temp = x;
		x = x1;
		x1 = temp;
	}
	if (y1 < y) {
		temp = y;
		y = y1;
		y1 = temp;
	}

	if (PrintDlg(&dialog)) {
		float scale = 1.6;
		RECT rect = LayerManager::instance->client_area;
		int rx = GetDeviceCaps(dialog.hDC, LOGPIXELSX);
		int ry = GetDeviceCaps(dialog.hDC, LOGPIXELSY);

		StartDoc(dialog.hDC, &info);
		StartPage(dialog.hDC);

		int rx1 = GetDeviceCaps(LayerManager::instance->GetLayer(1)->dc, LOGPIXELSX);
		int ry1 = GetDeviceCaps(LayerManager::instance->GetLayer(1)->dc, LOGPIXELSY);

		StretchBlt(dialog.hDC, 0, 0, (int)(scale * rect.right * ((float)(rx / rx1))),
			(int)(scale * rect.bottom * ((float)(ry / ry1))),
			LayerManager::instance->GetLayer(0)->dc, x, y, x1 - x, y1 - y, SRCCOPY);
		
		EndPage(dialog.hDC);
		EndDoc(dialog.hDC);
		DeleteDC(dialog.hDC);
	}
}
