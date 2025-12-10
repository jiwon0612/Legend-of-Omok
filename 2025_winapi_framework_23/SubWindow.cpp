#include "pch.h"
#include "SubWindow.h"
#include "Resource.h"
#include "Core.h"
#include<string>

using std::string;

SubWindow::SubWindow(HINSTANCE _hInst, wstring type, Vector2 pos, Vector2 size)
{
	m_hInst = _hInst;
	m_type = type;
	m_pos = pos;
	m_size = size;
	RegisterSubWindowClass();
	CreateSubWindow();
	ShowSubWindow();
	cout << 'c' << '\n';
}

SubWindow::~SubWindow()
{
	cout << string().assign(m_type.begin(),m_type.end()) << '\n';
	//cout << 'd' << '\n';
	//exit(0);
	//PostQuitMessage(0);	
	::SendMessage(m_hWnd, WM_CLOSE, 0, 0);
}

ATOM SubWindow::RegisterSubWindowClass()
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = SubWindow::WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = m_hInst;
	wcex.hIcon = LoadIcon(m_hInst, MAKEINTRESOURCE(IDI_MY2025WINAPIFRAMEWORK23));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = nullptr;
	wcex.lpszClassName = L"GameSub";
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return ::RegisterClassExW(&wcex);
}

void SubWindow::CreateSubWindow()
{
	m_hWnd = ::CreateWindowW(L"GameSub", L"SubWindow",
		WS_POPUP | WS_BORDER | WS_CAPTION | WS_VISIBLE,
		m_pos.x, m_pos.y,
		m_size.x, m_size.y,
		nullptr,
		nullptr,
		m_hInst,
		nullptr);
}

void SubWindow::ShowSubWindow()
{
	::ShowWindow(m_hWnd, SW_SHOW);
}

LRESULT SubWindow::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		// TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
		//Rectangle(hdc, 100, 100, 200, 200);
		EndPaint(hWnd, &ps);
	}
	break;
	//case WM_DESTROY:
	//	//PostQuitMessage(0);
	//	break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

int SubWindow::MessageLoop()
{
	MSG msg;

	// 기본 메시지 루프입니다:
	if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
	{
		if (msg.message != WM_QUIT)
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	else
	{

	}
	//GET_SINGLE(Core)->CleanUp();
	return (int)msg.wParam;
}
