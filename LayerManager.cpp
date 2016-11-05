#include "stdafx.h"
#include "LayerManager.h"

LayerManager *LayerManager::instance = NULL;

void LayerManager::Init(HWND hWin) {
	if (LayerManager::instance == NULL) {
		instance = new LayerManager(hWin);
	}
}

LayerManager::LayerManager(HWND hWin) {
	this->hWin = hWin;
	winDC = GetDC(hWin);
	
	GetClientRect(hWin, &client_area);
	
	for (int i = 0; i < NUM_LAYERS; i++) {
		layer[i] = new Layer(winDC, client_area);
	}
	metafile = new MetafileLayer(client_area.right, client_area.bottom);
}

void LayerManager::SetAllPensColor(COLORREF newColor) {
	for (int i = 0; i < NUM_LAYERS; i++) {
		layer[i]->SetPenColor(newColor);
	}

	metafile->SetPenColor(newColor);
}

void LayerManager::SetAllBrushColor(COLORREF newColor) {
	for (int i = 0; i < NUM_LAYERS; i++) {
		layer[i]->SetBrushColor(newColor);
	}

	metafile->SetBrushColor(newColor);
}

void LayerManager::SetAllPensWidth(int width) {
	for (int i = 0; i < NUM_LAYERS; i++) {
		layer[i]->SetPenWidht(width);
	}

	metafile->SetPenWidht(width);
}

void LayerManager::Clear() {
	COLORREF old_brush_color;

	for (int i = 0; i < NUM_LAYERS; i++) {
		old_brush_color = layer[i]->SetBrushColor(RGB(255, 255, 255));
		PatBlt(layer[i]->dc, 0, 0, client_area.right, client_area.bottom, PATCOPY);
	}
	metafile->New();

	SetAllBrushColor(old_brush_color);

	Lens::instance->NormalScale();
}

void LayerManager::DrawingImage(LPCTSTR path) {
	HENHMETAFILE hmetafile;
	ENHMETAHEADER metafile_header;
	RECT metafile_rect;

	hmetafile = GetEnhMetaFile(path);
	GetEnhMetaFileHeader(hmetafile, sizeof(ENHMETAHEADER), &metafile_header);
	SetRect(&metafile_rect, metafile_header.rclBounds.left, metafile_header.rclBounds.top,
		metafile_header.rclBounds.right, metafile_header.rclBounds.bottom);

	Clear();

	for (int i = 0; i < NUM_LAYERS; i++) {
		PlayEnhMetaFile(layer[i]->dc, hmetafile, &metafile_rect);
	}
	PlayEnhMetaFile(metafile->dc, hmetafile, &metafile_rect);

	DeleteEnhMetaFile(hmetafile);
}

Layer * LayerManager::GetLayer(int layer_id)
{
	if ((layer_id >= 0) && (layer_id < NUM_LAYERS)) {
		return layer[layer_id];
	}
	else {
		return layer[1];
	}
}

MetafileLayer * LayerManager::GetMetafile() {
	return metafile;
}

HDC LayerManager::GetWinDc() {
	return winDC;
}

