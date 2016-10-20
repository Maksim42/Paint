#pragma once

#include "LayerManager.h"

class Lens {
public:
	static Lens *instance;
	
	static void Init();
	void Scaling(HDC);
	POINT CalculationRealCordinate(int, int);
	void ZoomIn();
	void ZoomOut();
	void MoveRight();
	void MoveLeft();
	void MoveTop();
	void MoveBotom();
private:
	double scale;
	float x_vievw;
	float y_vievw;
	float x_size;
	float y_size;
	float horizontal_step;
	float vertical_step;
	float horizontal_scale;
	float vertical_scale;

	Lens();
	~Lens();
	int ÑalculationShift(int, float, float*);
	void CalculationScaleParam();
};

