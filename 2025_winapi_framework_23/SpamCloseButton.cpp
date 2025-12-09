#include "pch.h"
#include "SpamCloseButton.h"
#include "WindowManager.h"
#include "InputManager.h"
#include "GDISelector.h"

SpamCloseButton::SpamCloseButton(wstring windowType, Vec2 position, Vec2 size)
	: mousePos { 0, 0 }
{
	m_windowType = windowType;
	SetPos(position);
	SetSize(size);
}

void SpamCloseButton::Update()
{
	if (GET_KEYDOWN(KEY_TYPE::LBUTTON))
	{
		mousePos = GET_SINGLE(WindowManager)->GetMousePoint(m_windowType);
		Vec2 pos = GetPos();
		Vec2 size = GetSize();
		if (mousePos.x >= pos.x && mousePos.x <= pos.x + size.x &&
			mousePos.y >= pos.y && mousePos.y <= pos.y + size.y)
		{
			SubWindow* targetWindow = GET_SINGLE(WindowManager)->GetSubWindow(m_windowType);
			if (targetWindow)
			{
				GET_SINGLE(WindowManager)->RemoveWindow(targetWindow);
			}
		}
	}
}

void SpamCloseButton::Render(HDC _hdc)
{
	RECT_RENDER(_hdc, GetPos().x, GetPos().y, GetSize().x, GetSize().y, RGB(255, 0, 0));
}
