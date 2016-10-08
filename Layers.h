#pragma once

#define ChangeObject(hdc, obj) DeleteObject(SelectObject(hdc, obj));

class Layers { 
public:
	static Layers  *instance;
	HWND			hWin;
	HDC				winDC;
	HDC				main;
	HDC				temporari;
	HDC				scale;
	RECT			clientArea;

	static void		Init(HWND);
private:
	HBRUSH			brush;
	HPEN			pen;

					Layers(HWND);
	HDC				GetLayer();
};