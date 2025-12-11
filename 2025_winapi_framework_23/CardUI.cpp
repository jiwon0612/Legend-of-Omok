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

	int curX = (pos.x - size.x);
	int curY = (pos.y - size.y);

	/*::BitBlt(_hdc
		, (int)(pos.x - size.x / 2)
		, (int)(pos.y - size.y / 2)
		, width
		, height
		, m_cardTex->GetTextureDC()
		, 0, 0, SRCCOPY);*/
	/*if (m_isHover)
		RECT_RENDER(_hdc, pos.x, pos.y, size.x + m_outlineThickness / 2, size.y + m_outlineThickness / 2);*/

	//화질 올리기
	SetStretchBltMode(_hdc, HALFTONE);
	SetBrushOrgEx(_hdc, 0, 0, nullptr); // HALFTONE 사용할 때 필수

	::StretchBlt(_hdc
		, (int)(pos.x - size.x / 2) - 40
		, (int)(pos.y - size.y / 2) - 40
		, (int)(size.x) + 80
		, (int)(size.y) + 80
		, m_cardTex->GetTextureDC()
		, 0, 0, width, height, SRCCOPY);

	if (m_isInit)
	{
		//아이콘
		width = m_cardIconTex->GetWidth();
		height = m_cardIconTex->GetHeight();

		/*::BitBlt(_hdc
			, (pos.x - size.x / 2)
			, (pos.y - size.y / 2) + height / 2
			, 64
			, 47
			, m_cardIconTex->GetTextureDC()
			, 0, 0, SRCCOPY);*/
		::StretchBlt(_hdc
			, (int)(pos.x - size.x / 2) -12 //- 29 + 17
			, (int)(pos.y - size.y / 2) -10 //- 30 + 20
			, (int)(size.x) + 23 //+ 64 + 59
			, (int)(size.y / 2)//+ 47 + 28
			, m_cardIconTex->GetTextureDC()
			, 0, 0, width, height, SRCCOPY);

		//폰트
		SetBkMode(_hdc, TRANSPARENT);

		SetTextColor(_hdc, RGB(0, 0, 0));

		HFONT fontSet = CreateFont(
			15 + (5*((size.x - 100)/50)), 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
			DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
			ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_SWISS, L"맑은 고딕"
		);
		HFONT font = (HFONT)SelectObject(_hdc, fontSet);


		//TextOut(_hdc, (pos.x - size.x) + 50, (pos.y - size.y) + 50, m_cardInfo->name.c_str(), m_cardInfo->name.length());
		RECT rect = {
			(int)(pos.x) - 13 - 50 - (int)((size.x - 100) * 0.3f),
			(int)(pos.y) + 80 - 75,
			(int)(pos.x + size.x / 2) + 12 - (int)((size.x - 100) * 0.1f),
			(int)(pos.y + size.y / 2) - 45 - (int)((size.x - 100) * 0.34f)
		};

		//이름
		DrawText(_hdc, m_cardInfo->name.c_str(), -1, &rect,
			DT_CENTER | DT_VCENTER | DT_WORDBREAK);
		/*DrawText(_hdc, m_cardInfo->name.c_str(), m_cardInfo->name.length(),
			,
			DT_CENTER | DT_VCENTER | DT_SINGLELINE);*/

		//TextOut(_hdc, (pos.x - size.x), (pos.y - size.y) + 20, m_cardInfo->description.c_str(), m_cardInfo->description.length());
		rect = {
			(int)(pos.x) - 13 - 50 - (int)((size.x - 100) * 0.30f),
			(int)(pos.y + size.y / 2) - 35 - (int)((size.x - 100) * 0.34f),
			(int)(pos.x + size.x / 2) + 12 - (int)((size.x - 100) * 0.10f),
			(int)(pos.y) + 105 + (int)((size.x - 100) * 0.44f)
		};

		//설명
		DrawText(_hdc, m_cardInfo->description.c_str(), -1, &rect,
			DT_CENTER | DT_VCENTER | DT_WORDBREAK);

		fontSet = CreateFont(
			70, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
			DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
			ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_SWISS, L"맑은 고딕"
		);
		font = (HFONT)SelectObject(_hdc, fontSet);

		::DeleteObject(fontSet);
		::DeleteObject(font);
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
