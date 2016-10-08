#include "stdafx.h"
#include "ToolManager.h"

ToolManager *ToolManager::instance = NULL;

ToolManager::ToolManager() {
	tools[TID_TOOL] = new Tool();
	tools[TID_PENSIL] = new Pensil();

	//tool = new Pensil();

	SetTool(TID_TOOL);
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
