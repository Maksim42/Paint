#pragma once

struct PenProp {
	int style;
	int width;
	COLORREF color;
};

class Layer {
public:
	HDC dc;
	
	Layer(HDC, RECT);
	~Layer();
	COLORREF SetPenColor(COLORREF);
	int SetPenWidht(int);
	HPEN SetPen(int, int, COLORREF);
	PenProp SetPen(PenProp);
	COLORREF SetBrushColor(COLORREF);
	void BrushOff();
	void BrushOn();
protected:
	int penStyle;
	int penWidth;
	COLORREF penColor;
	COLORREF brushColor;
	HPEN def_pen;
	HBITMAP def_bitmap;
	HBRUSH def_brush;

	Layer();
};

