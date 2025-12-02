#include "pch.h"
#include "Stone.h"

Stone::Stone(StoneType type, Vec2 size, Vec2 pos)
	: m_type(type)
{
	SetSize(size);
	SetPos(pos);
}

Stone::~Stone()
{
}

void Stone::Render(HDC _hdc)
{
	if (m_blind) return;
	// 바둑돌 색상 설정
	COLORREF stoneColor = (m_type == StoneType::BLACK) ? RGB(30, 30, 30) : RGB(245, 245, 245);
	HBRUSH stoneBrush = CreateSolidBrush(stoneColor);
	HBRUSH oldBrush = (HBRUSH)SelectObject(_hdc, stoneBrush);
	Vec2 pos = GetPos();
	Vec2 size = GetSize();
	// 바둑돌 그리기
	Ellipse(_hdc,
		static_cast<int>(pos.x - size.x / 2),
		static_cast<int>(pos.y - size.y / 2),
		static_cast<int>(pos.x + size.x / 2),
		static_cast<int>(pos.y + size.y / 2));
	SelectObject(_hdc, oldBrush);
	DeleteObject(stoneBrush);
}

void Stone::Update()
{
}
