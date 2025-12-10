#pragma once
class SubWindow
{
public:
	SubWindow(HINSTANCE _hInst, wstring type, Vector2 pos, Vector2 size, wstring title);
	virtual ~SubWindow();

public:
	ATOM RegisterSubWindowClass();
	void CreateSubWindow();
	void ShowSubWindow();
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	int MessageLoop();
	HWND GetHwnd() const { return m_hWnd; }
	wstring GetType() const { return m_type; }
	Vec2 GetSize() const { return m_size; }

private:
	HINSTANCE m_hInst;
	HWND m_hWnd;
	wstring m_type;
	Vector2 m_size;
	Vector2 m_pos;
	wstring m_title;
};

