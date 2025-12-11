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
	/*for (size_t i = 0; i < m_windows.size(); i++)
	{
		m_windows[i]->MessageLoop();
	}*/

	for (auto& window : m_windows)
	{
		if (m_windows.size() <= 0)
			break;

		if (window.second == nullptr)
			continue;
		window.second->MessageLoop();
	}
}

void WindowManager::AddWindow(SubWindow* window)
{
	m_windows[window->GetType()] = window;
	WindowAPIs* apis = new WindowAPIs(window->GetHwnd());
	m_windowAPIs[window->GetType()] = apis;
}

void WindowManager::RemoveWindow(SubWindow* window)
{
	if (m_windowAPIs[window->GetType()] != nullptr)
	{
		SAFE_DELETE(m_windowAPIs[window->GetType()]);
	}

	m_windowAPIs.erase(window->GetType());

	m_windows.erase(window->GetType());
	SAFE_DELETE(window);
}

void WindowManager::RemoveAllWindow()
{
	for (auto window : m_windows)
	{
		SAFE_DELETE(window.second);
		//RemoveWindow(window.second);
	}
	for (auto& window : m_windowAPIs)
	{
		SAFE_DELETE(window.second);
	}
	m_windowAPIs.clear();
	m_windows.clear();
}

void WindowManager::DisplayAllDC()
{
	for (auto windows : m_windowAPIs)
	{
		BitBlt(windows.second->GetMainDC(), 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT,
			windows.second->GetBackDC(), 0, 0, SRCCOPY);
	}
}

void WindowManager::ClearAllDC()
{
	for (auto windows : m_windowAPIs)
	{
		PatBlt(windows.second->GetBackDC(), 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, WHITENESS);
	}
}

POINT WindowManager::GetMousePoint(wstring key)
{
	::GetCursorPos(&m_mousePos);
	::ScreenToClient(m_windowAPIs[key]->GetHwnd(), &m_mousePos);
	return m_mousePos;
}
