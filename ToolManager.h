#pragma once

#include "DrawingTools.h"

class ToolManager
{
public:
	static ToolManager *instance;
	Tool *tool;

	static void	Init();
	int SetTool(int);
private:
	Tool *tools[TOOLNUM];

	ToolManager();
};

