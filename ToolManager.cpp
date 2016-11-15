#include "stdafx.h"
#include "ToolManager.h"

ToolManager *ToolManager::instance = NULL;

ToolManager::ToolManager() {
	tools[TID_PENSIL] = new Pensil();
	tools[TID_LINE] = new Line();
	tools[TID_PRINT] = new PrinterTool();
	tools[TID_RECT] = new RectangleTool();
	tools[TID_ELLIPSE] = new EllipseTool();
	tools[TID_POLYLINE] = new Polylines();
	tools[TID_POLYGON] = new PolygonTool();

	SetTool(TID_PENSIL);
}

void ToolManager::Init() {
	if (ToolManager::instance == NULL) {
		ToolManager::instance = new ToolManager();
	}
}

int ToolManager::SetTool(int id) {
	if ((id < TOOLNUM) && (id >= 0)) {
		tool = tools[id];

		return id;
	}

	return -1;
}
