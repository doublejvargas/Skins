#pragma once

#include "Render/DisplayManager.h"

class ApplicationManager
{
public:
	ApplicationManager();
	virtual ~ApplicationManager();

	void Start();

private:
	DisplayManager* m_DisplayManager = nullptr;
};
