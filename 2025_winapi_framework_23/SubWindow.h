#pragma once
class SubWindow
{
public:
	SubWindow(HINSTANCE _hInst);
	virtual ~SubWindow();

public:
	ATOM RegisterSubWindowClass();
	void CreateSubWindow();
	void ShowSubWindow();
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	int MessageLoop();

private:
	HINSTANCE m_hInst;
	HWND m_hWnd;
};

