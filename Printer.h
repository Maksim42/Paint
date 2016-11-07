#pragma once
#include <CommDlg.h>
#include "LayerManager.h"

class Printer {
public:
	static Printer *instance;

	static void Init(HWND);
	Printer(HWND);
	~Printer();
	void Print(int, int, int, int);
private:
	PRINTDLG dialog;
	DOCINFO info;
};

