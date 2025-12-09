#include "pch.h"
#include "SpamWindow.h"
#include "SceneManager.h"

SpamWindow::~SpamWindow()
{
	for (Object* obj : m_objects)
	{
		GET_SINGLE(SceneManager)->RequestDestroy(obj);
	}
	m_objects.clear();
}

void SpamWindow::AddObject(Object* obj)
{
	m_objects.push_back(obj);
}
