#pragma once
class SubWindow;

class WindowManager
{
	DECLARE_SINGLE(WindowManager);

public:
	void Init(HINSTANCE _hInst);
	void Update();
	void AddWindow(SubWindow* window);
	void RemoveWindow(SubWindow* window);
	HINSTANCE GetHInstance() { return m_hInst; }
private:
	vector<SubWindow*> m_windows;
	HINSTANCE m_hInst;
};

