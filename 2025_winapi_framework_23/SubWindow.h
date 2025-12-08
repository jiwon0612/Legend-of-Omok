#pragma once
class SubWindow
{
public:
	SubWindow(HINSTANCE _hInst, wstring type);
	virtual ~SubWindow();

public:
	ATOM RegisterSubWindowClass();
	void CreateSubWindow();
	void ShowSubWindow();
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	int MessageLoop();
	HWND GetHwnd() const { return m_hWnd; }
	wstring GetType() const { return m_type; }

private:
	HINSTANCE m_hInst;
	HWND m_hWnd;
	wstring m_type;
};

