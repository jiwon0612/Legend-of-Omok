#include "pch.h"
#include "WindowManager.h"
#include "SubWindow.h"
#include "WindowAPIs.h"

void WindowManager::Init(HINSTANCE _hInst)
{
	m_hInst = _hInst;
}

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
	WindowAPIs* apis = new WindowAPIs(window->GetHwnd());
	m_windowAPIs[window->GetType()] = apis;
}

void WindowManager::RemoveWindow(SubWindow* window)
{
	if (m_windowAPIs[window->GetType()] != nullptr)
		SAFE_DELETE(m_windowAPIs[window->GetType()]);

	m_windowAPIs.erase(window->GetType());
	m_windows.erase(std::remove(m_windows.begin(), m_windows.end(), window), m_windows.end());
}
