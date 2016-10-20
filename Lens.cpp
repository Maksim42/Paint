#include "stdafx.h"

#include "Lens.h"

Lens *Lens::instance = NULL;

Lens::Lens() {
	scale = 1;
	x_vievw = (int)LayerManager::instance->client_area.right / 2;
	y_vievw = (int)LayerManager::instance->client_area.bottom /2;

	CalculationScaleParam();
}

void Lens::Init() {
	if (Lens::instance == NULL) {
		instance = new Lens();
	}
}

void Lens::Scaling(HDC main_dc) {
	int x_ = ÑalculationShift(LayerManager::instance->client_area.right, x_size, &x_vievw);
	int y_ = ÑalculationShift(LayerManager::instance->client_area.bottom, y_size, &y_vievw);

	XFORM xform;
	xform.eM11 = Lens::instance->scale;
	xform.eM12 = 0;
	xform.eM21 = 0;
	xform.eM22 = Lens::instance->scale;
	xform.eDx = 0;
	xform.eDy = 0;

	SetGraphicsMode(main_dc, GM_ADVANCED);
	BOOL ret = SetWorldTransform(main_dc, &xform);

	BitBlt(main_dc, 0, 0, LayerManager::instance->client_area.right, LayerManager::instance->client_area.bottom,
		LayerManager::instance->GetLayer(1)->dc, x_, y_, SRCCOPY);
}

POINT Lens::CalculationRealCordinate(int x, int y) {
	POINT real_cordinate;
	real_cordinate.x = (x_vievw - x_size / 2) + x * horizontal_scale;
	real_cordinate.y = (y_vievw - y_size / 2) + y * vertical_scale;

	return real_cordinate;
}

void Lens::ZoomIn() {
	if (scale < 3) {
		scale = scale + 0.03;
		CalculationScaleParam();
	}
}

void Lens::ZoomOut() {
	if (scale > 1) {
		scale = scale - 0.03;
		CalculationScaleParam();
	}
}

void Lens::MoveRight() {
	x_vievw += horizontal_step;
}

void Lens::MoveLeft() {
	x_vievw -= horizontal_step;
}

void Lens::MoveTop() {
	y_vievw -= vertical_step;
}

void Lens::MoveBotom() {
	y_vievw += vertical_step;
}

void Lens::NormalScale() {
	scale = 1;
	x_vievw = (int)LayerManager::instance->client_area.right / 2;
	y_vievw = (int)LayerManager::instance->client_area.bottom / 2;

	CalculationScaleParam();
}

void Lens::CalculationScaleParam() {
	x_size = LayerManager::instance->client_area.right / scale;
	y_size = LayerManager::instance->client_area.bottom / scale;
	horizontal_step = x_size * 0.04;
	vertical_step = y_size * 0.04;
	horizontal_scale = x_size / LayerManager::instance->client_area.right;
	vertical_scale = y_size / LayerManager::instance->client_area.bottom;
}

int Lens::ÑalculationShift(int real_size, float size,float *shift) {
	float half_size = size / 2;
	int scale_shift = (int)(*shift - half_size);
	int border = (int)real_size - size;

	if (scale_shift < 0) {
		*shift = half_size;
		scale_shift = 0;
	} else {
		if (scale_shift > border) {
			*shift = border + half_size;
			scale_shift = border;
		}
	}

	return scale_shift;
}
