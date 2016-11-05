#include "stdafx.h"
#include "MetafileLayer.h"

MetafileLayer::MetafileLayer(int right, int bottom) : Layer() {
	COLORREF white = RGB(255, 255, 255);
	border.x = right;
	border.y = bottom;

	dc = CreateEnhMetaFile(NULL, NULL, NULL, L"PaintSave\0");
	SetPixel(dc, 0, 0, white);
	SetPixel(dc, border.x, border.y, white);

	def_pen = SetPen(PS_SOLID, 1, RGB(10, 20, 30));

	brushColor = white;
	HBRUSH newBrush = CreateSolidBrush(brushColor);
	def_brush = (HBRUSH)SelectObject(dc, newBrush);
}

MetafileLayer::~MetafileLayer() {
	DeleteObject(SelectObject(dc, def_pen));
	DeleteObject(SelectObject(dc, def_brush));

	hmetafile = CloseEnhMetaFile(dc);
	DeleteEnhMetaFile(hmetafile);
}

void MetafileLayer::Save(LPCTSTR path) {
	ENHMETAHEADER metafile_header;
	RECT metafile_rect;

	hmetafile = CloseEnhMetaFile(dc);
	
	GetEnhMetaFileHeader(hmetafile, sizeof(ENHMETAHEADER), &metafile_header);
	SetRect(&metafile_rect, metafile_header.rclBounds.left, metafile_header.rclBounds.top,
		metafile_header.rclBounds.right, metafile_header.rclBounds.bottom);

	HENHMETAFILE save =  CopyEnhMetaFile(hmetafile, path);
	DeleteEnhMetaFile(save);

	dc = CreateEnhMetaFile(NULL, NULL, NULL, L"PaintSave\0");
	PlayEnhMetaFile(dc, hmetafile, &metafile_rect);

	DeleteEnhMetaFile(hmetafile);
}

void MetafileLayer::New() {
	DeleteObject(SelectObject(dc, def_pen));
	DeleteObject(SelectObject(dc, def_brush));
	hmetafile = CloseEnhMetaFile(dc);
	DeleteEnhMetaFile(hmetafile);

	dc = CreateEnhMetaFile(NULL, NULL, NULL, L"Paint\0");
	SetPixel(dc, 0, 0, RGB(255, 255, 255));
	SetPixel(dc, border.x, border.y, RGB(255, 255, 255));

	HPEN newPen = CreatePen(penStyle, penWidth, penColor);
	def_pen = (HPEN) SelectObject(dc, newPen);

	HBRUSH newBrush = CreateSolidBrush(brushColor);
	def_brush = (HBRUSH)SelectObject(dc, newBrush);
}
