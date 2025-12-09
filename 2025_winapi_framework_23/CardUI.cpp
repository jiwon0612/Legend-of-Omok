#include "pch.h"
#include "CardUI.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "Texture.h"
#include "CardInfo.h"
#include "Card.h"
#include "InputManager.h"
#include "CardManager.h"
#include "WindowManager.h"

CardUI::CardUI()
	: m_cardInfo(nullptr)
	, m_cardTex(nullptr)
	, m_cardIconTex(nullptr)
	, m_isInit(false)
	, m_isHover(false)
	, m_hoverSizeOffset({ 50,50 })
	, m_defultSize(GetSize())
	, m_outlineThickness(1.f)
{
	m_cardTex = GET_SINGLE(ResourceManager)->GetTexture(L"CardImage");
	SetScaleTweenSpeed(5);
	SetMoveTweenSpeed(3);
}

CardUI::~CardUI()
{
}

void CardUI::Init(CardInfo* _cardInfo)
{
	m_defultSize = GetSize();
	m_cardInfo = _cardInfo;
	m_cardIconTex = GET_SINGLE(ResourceManager)->GetTexture(m_cardInfo->iconName);
	m_isInit = true;
}

void CardUI::Update()
{
	TweeningObject::Update();

	if (!m_isInit)
		return;

	//POINT mouse = GET_SINGLE(InputManager)->GetMousePos();
	POINT mouse = GET_SINGLE(WindowManager)->GetMousePoint(GetWindowType());
	Vector2 mousePos = { (float)mouse.x, (float)mouse.y };

	Vector2 pos = GetPos();
	Vector2 size = GetSize();
	//::PtInRect()
	SetIsHover(mousePos.x > (pos.x - size.x / 2) &&
		mousePos.x < (pos.x + size.x / 2) &&
		mousePos.y >(pos.y - size.y / 2) &&
		mousePos.y < (pos.y + size.y / 2));

	if (m_isHover && GET_KEYDOWN(KEY_TYPE::LBUTTON) && !GetIsDead())
	{
		GET_SINGLE(CardManager)->UseCard();
		m_cardInfo->card->CardSkill();
		//GET_SINGLE(SceneManager)->GetCurScene()->RequestDestroy(this);
	}
	//static Vector2 offset = { 0.f, 0.f };

	/*if (GET_KEYDOWN(KEY_TYPE::LBUTTON))
	{
		POINT mousePos = GET_SINGLE(InputManager)->GetMousePos();
		Vector2 position = GetPos();
		offset = {position.x - mousePos.x,position.y - mousePos.y};
	}
	else if (GET_KEY(KEY_TYPE::LBUTTON))
	{
		POINT mousePos = GET_SINGLE(InputManager)->GetMousePos();
		SetPos({ (float)mousePos.x + offset.x, (float)mousePos.y + offset.y });
	}
	else if (GET_KEYUP(KEY_TYPE::LBUTTON))
	{
		offset = { 0,0 };
	}*/

	/*if (GET_KEYDOWN(KEY_TYPE::LBUTTON))
	{
		POINT mousePos = GET_SINGLE(InputManager)->GetMousePos();
		Vector2 position((float)mousePos.x, (float)mousePos.y);
		MoveToPosition(GetPos(), position);
	}*/

}

void CardUI::Render(HDC _hdc)
{
	Vector2 pos = GetPos();
	Vector2 size = GetSize();

	LONG width = m_cardTex->GetWidth();
	LONG height = m_cardTex->GetHeight();

	/*::BitBlt(_hdc
		, (int)(pos.x - size.x / 2)
		, (int)(pos.y - size.y / 2)
		, width
		, height
		, m_cardTex->GetTextureDC()
		, 0, 0, SRCCOPY);*/
	/*if (m_isHover)
		RECT_RENDER(_hdc, pos.x, pos.y, size.x + m_outlineThickness / 2, size.y + m_outlineThickness / 2);*/

	::StretchBlt(_hdc
		, (int)(pos.x - size.x / 2)
		, (int)(pos.y - size.y / 2)
		, (int)(size.x)
		, (int)(size.y)
		, m_cardTex->GetTextureDC()
		, 0, 0, width, height, SRCCOPY);

	if (m_isInit)
	{
		TextOut(_hdc, pos.x, pos.y, m_cardInfo->name.c_str(), m_cardInfo->name.length());
		/*DrawText(_hdc, m_cardInfo->name.c_str(), m_cardInfo->name.length(),
			,
			DT_CENTER | DT_VCENTER | DT_SINGLELINE);*/
		TextOut(_hdc, pos.x, pos.y + 20, m_cardInfo->description.c_str(), m_cardInfo->description.length());

		width = m_cardIconTex->GetWidth();
		height = m_cardIconTex->GetHeight();

		::BitBlt(_hdc
			, (pos.x - size.x / 2)
			, (pos.y - size.y / 2) + height / 2
			, width
			, height
			, m_cardIconTex->GetTextureDC()
			, 0, 0, SRCCOPY);
	}
}

void CardUI::SetIsHover(bool value)
{
	if (m_isHover != value)
	{
		if (value)
			ScaleToSize(m_defultSize, m_defultSize + m_hoverSizeOffset);
		else
			ScaleToSize(m_defultSize + m_hoverSizeOffset, m_defultSize);
	}
	m_isHover = value;
}
