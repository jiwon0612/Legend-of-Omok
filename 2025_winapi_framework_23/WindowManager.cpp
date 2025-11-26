#include "pch.h"
#include "WindowManager.h"
#include "SubWindow.h"

void WindowManager::Update()
{
	for (size_t i = 0; i < m_windows.size(); i++)
	{
		m_windows[i]->MessageLoop();
	}
}

void WindowManager::AddWindow(SubWindow* window)
{
	m_windows.push_back(window);
}

void WindowManager::RemoveWindow(SubWindow* window)
{

}
