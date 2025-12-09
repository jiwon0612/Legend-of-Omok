#pragma once
class SubWindow;
class WindowAPIs;

class WindowManager
{
	DECLARE_SINGLE(WindowManager);

public:
	void Init(HINSTANCE _hInst);
	void Update();
	void AddWindow(SubWindow* window);
	void RemoveWindow(SubWindow* window);
	void RemoveAllWindow();
	void DisplayAllDC();
	void ClearAllDC();
	HINSTANCE GetHInstance() { return m_hInst; }
	POINT GetMousePoint(wstring key);
	WindowAPIs* GetWindowAPIs(wstring type)
	{
		auto iter = m_windowAPIs.find(type);
		if (iter != m_windowAPIs.end())
			return iter->second;
		return nullptr;
	}
	SubWindow* GetSubWindow(wstring type)
	{
		auto iter = m_windows.find(type);
		if (iter != m_windows.end())
			return iter->second;
		return nullptr;
	}
private:
	unordered_map<wstring, WindowAPIs*> m_windowAPIs;
	unordered_map<wstring, SubWindow*> m_windows;
	HINSTANCE m_hInst;
	POINT m_mousePos;
};

