#pragma once

class Layer {
public:
	HDC dc;
	
	Layer(HDC, RECT);
	~Layer();
	COLORREF SetPenColor(COLORREF);
	int SetPenWidht(int);
	HPEN SetPen(int, int, COLORREF);
	COLORREF SetBrushColor(COLORREF);
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

