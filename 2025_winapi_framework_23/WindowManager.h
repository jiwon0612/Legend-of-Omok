#pragma once
class SubWindow;

class WindowManager
{
	DECLARE_SINGLE(WindowManager);

public:
	void Update();
	void AddWindow(SubWindow* window);
	void RemoveWindow(SubWindow* window);
private:
	vector<SubWindow*> m_windows;
};

