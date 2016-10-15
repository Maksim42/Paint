#include "stdafx.h"
#include "Layer.h"

Layer::Layer(HDC mainDc, RECT clientRect) {
	dc = CreateCompatibleDC(mainDc);

	HBITMAP BitMp = CreateCompatibleBitmap(mainDc, clientRect.right, clientRect.bottom);
	DeleteObject(SelectObject(dc, BitMp));

	SetPen(PS_SOLID, 1, RGB(10, 20, 30));
	
	SetBrushColor(RGB(255, 255, 255));
	PatBlt(dc, 0, 0, clientRect.right, clientRect.bottom, PATCOPY);
}

Layer::~Layer()
{
}

HPEN Layer::SetPen(int style, int width, COLORREF color) {
	penStyle = style;
	penWidth = width;
	penColor = color;

	HPEN newPen = CreatePen(penStyle, penWidth, penColor);
	HPEN oldPen = (HPEN)SelectObject(dc, newPen);

	return oldPen;
}

COLORREF Layer::SetPenColor(COLORREF newColor) {
	COLORREF oldColor = penColor;
	penColor = newColor;

	HPEN newPen = CreatePen(penStyle, penWidth, penColor);
	DeleteObject(SelectObject(dc, newPen));

	return oldColor;
}

int Layer::SetPenWidht(int newWidth) {
	int oldW = penWidth;
	penWidth = newWidth;

	HPEN newPen = CreatePen(penStyle, penWidth, penColor);
	DeleteObject(SelectObject(dc, newPen));

	return oldW;
}

COLORREF Layer::SetBrushColor(COLORREF newColor) {
	int oldColor = brushColor;
	brushColor = newColor;

	HBRUSH newBrush = CreateSolidBrush(newColor);
	DeleteObject(SelectObject(dc, newBrush));

	return oldColor;
}
