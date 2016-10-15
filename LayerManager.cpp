#include "stdafx.h"
#include "LayerManager.h"

LayerManager *LayerManager::instance = NULL;

LayerManager::LayerManager(HWND hWin) {
	this->hWin = hWin;
	winDC = GetDC(hWin);
	
	GetClientRect(hWin, &client_area);
	
	for (int i = 0; i < NUM_LAYERS; i++) {
		layer[i] = new Layer(winDC, client_area);
	}
}

void LayerManager::SetAllPensColor(COLORREF newColor) {
	for (int i = 0; i < NUM_LAYERS; i++) {
		layer[i]->SetPenColor(newColor);
	}
}

void LayerManager::SetAllBrushColor(COLORREF newColor) {
	for (int i = 0; i < NUM_LAYERS; i++) {
		layer[i]->SetBrushColor(newColor);
	}
}

void LayerManager::SetAllPensWidth(int width) {
	for (int i = 0; i < NUM_LAYERS; i++) {
		layer[i]->SetPenWidht(width);
	}
}

void LayerManager::Init(HWND hWin) {
	if (LayerManager::instance == NULL) {
		instance = new LayerManager(hWin);
	}
}

Layer * LayerManager::GetLayer(int layer_id)
{
	if ((layer_id >= 0) && (layer_id < NUM_LAYERS)) {
		return layer[layer_id];
	}
	else {
		return layer[0];
	}
	return nullptr;
}

