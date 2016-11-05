#pragma once
#include "Layer.h"

class MetafileLayer : public Layer{
public:
	MetafileLayer(int, int);
	~MetafileLayer();
	void Save(LPCTSTR path);
	void New();
private:
	HENHMETAFILE hmetafile;
	POINT border;
};

