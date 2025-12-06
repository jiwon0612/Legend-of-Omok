#pragma once

class WindowAPIs
{
public:
	WindowAPIs(HWND _hWnd);
	~WindowAPIs();
public:
	const HDC& GetMainDC() const { return m_hDC; }
	const HDC& GetBackDC() const { return m_hBackDC; }
	const HBITMAP& GetBackBitmap() const { return m_hBackBit; }
private:
	HWND m_hWnd;
	HDC  m_hDC;
	HBITMAP m_hBackBit;
	HDC	    m_hBackDC; 
};
