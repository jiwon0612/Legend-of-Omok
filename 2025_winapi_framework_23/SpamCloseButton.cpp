#include "pch.h"
#include "SpamCloseButton.h"
#include "WindowManager.h"
#include "InputManager.h"
#include "GDISelector.h"
#include "ResourceManager.h"
#include "Texture.h"

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
		if (mousePos.x >= pos.x - size.x / 2 && mousePos.x <= pos.x + size.x / 2 &&
			mousePos.y >= pos.y - size.y / 2 && mousePos.y <= pos.y + size.y / 2)
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
	Texture* buttonTexture = GET_SINGLE(ResourceManager)->GetTexture(L"CloseButton");
	if (buttonTexture)
	{
		Vec2 pos = GetPos();
		Vec2 size = GetSize();
		BitBlt(
			_hdc,
			static_cast<int>(pos.x - size.x / 2),
			static_cast<int>(pos.y - size.y / 2),
			static_cast<int>(size.x),
			static_cast<int>(size.y),
			buttonTexture->GetTextureDC(),
			0,
			0,
			SRCCOPY
		);
	}
}
