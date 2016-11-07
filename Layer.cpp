#include "stdafx.h"
#include "Layer.h"

Layer::Layer(HDC mainDc, RECT clientRect) {
	dc = CreateCompatibleDC(mainDc);

	HBITMAP BitMp = CreateCompatibleBitmap(mainDc, clientRect.right, clientRect.bottom);
	def_bitmap = (HBITMAP) SelectObject(dc, BitMp);

	def_pen = SetPen(PS_SOLID, 1, RGB(10, 20, 30));
	
	brushColor = RGB(255, 255, 255);
	HBRUSH newBrush = CreateSolidBrush(brushColor);
	def_brush = (HBRUSH) SelectObject(dc, newBrush);
	PatBlt(dc, 0, 0, clientRect.right, clientRect.bottom, PATCOPY);
}

Layer::Layer() {
}

Layer::~Layer() {
	DeleteObject(SelectObject(dc, def_bitmap));
	DeleteObject(SelectObject(dc, def_pen));
	DeleteObject(SelectObject(dc, def_brush));
}

HPEN Layer::SetPen(int style, int width, COLORREF color) {
	penStyle = style;
	penWidth = width;
	penColor = color;

	HPEN newPen = CreatePen(penStyle, penWidth, penColor);
	HPEN oldPen = (HPEN)SelectObject(dc, newPen);

	return oldPen;
}

PenProp Layer::SetPen(PenProp pp) {
	PenProp old_pp;
	old_pp.style = penStyle;
	old_pp.width = penWidth;
	old_pp.color = penColor;

	penStyle = pp.style;
	penWidth = pp.width;
	penColor = pp.color;

	HPEN newPen = CreatePen(penStyle, penWidth, penColor);
	HGDIOBJ oldPen = SelectObject(dc, newPen);
	DeleteObject(oldPen);

	return old_pp;
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

void Layer::BrushOff() {
	HBRUSH new_brush = (HBRUSH) GetStockObject(NULL_BRUSH);
	DeleteObject(SelectObject(dc, new_brush));
}

void Layer::BrushOn() {
	SelectObject(dc, CreateSolidBrush(brushColor));
}
