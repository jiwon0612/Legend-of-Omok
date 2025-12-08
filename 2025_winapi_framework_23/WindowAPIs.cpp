#include "pch.h"
#include "WindowAPIs.h"

WindowAPIs::WindowAPIs(HWND _hWnd)
{
	m_hWnd = _hWnd;
	m_hDC = ::GetDC(m_hWnd);

	m_hBackBit = 0;
	m_hBackDC = 0;

	m_hBackBit = ::CreateCompatibleBitmap(m_hDC, WINDOW_WIDTH, WINDOW_HEIGHT);
	m_hBackDC = ::CreateCompatibleDC(m_hDC);

	::SelectObject(m_hBackDC, m_hBackBit);
}

WindowAPIs::~WindowAPIs()
{
	::DeleteDC(m_hBackDC);
	::DeleteObject(m_hBackBit);
	::ReleaseDC(m_hWnd, m_hDC);
}
