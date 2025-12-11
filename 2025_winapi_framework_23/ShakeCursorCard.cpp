#include "pch.h"
#include "ShakeCursorCard.h"

ShakeCursorCard::ShakeCursorCard() 
    : isBlind(false)
	, _timer(0)
	, _shakeDelay(0.05f)
	, _isRight(false)
{
}

ShakeCursorCard::~ShakeCursorCard()
{
}

void ShakeCursorCard::ShakeCursor()
{
	_timer += fDT;
	if (_timer <= _shakeDelay)
		return;

    int amount = 15;
    int times = 10;
    int delay = 1;

    POINT p;
    GetCursorPos(&p); // 현재 위치 저장

    //for (int i = 0; i < times; i++)
    //{
    //    SetCursorPos(p.x + (i % 2 == 0 ? amount : -amount), p.y);
    //    Sleep(delay); //버벅 거릴려고
    //}

    if (_isRight)
	{
		SetCursorPos(p.x + amount, p.y);
		_isRight = false;
	}
	else
	{
		SetCursorPos(p.x - amount, p.y);
		_isRight = true;
	}

    //저세상 가는 거 방지
    //SetCursorPos(p.x, p.y);
}

void ShakeCursorCard::ReallySkill()
{
    isBlind = true;
}

void ShakeCursorCard::NextTurn()
{
    isBlind = false;
    isSkill = false;
}

void ShakeCursorCard::Update()
{
    if (!isSkill) return;

    if (!isBlind &&
        curPlayer != GET_SINGLE(BoardManager)->GetCurrentPlayer()) //턴 바뀜
    {
        ReallySkill();
    }

    if (!isBlind) return;
    ShakeCursor();

    if (curPlayer == GET_SINGLE(BoardManager)->GetCurrentPlayer()) //턴 바뀜
    {
        NextTurn();
        return;
    }
}
void ShakeCursorCard::Render(HDC _hdc)
{
    if (!isSkill) return;
}

void ShakeCursorCard::CardSkill()
{
    isSkill = true;
    curPlayer = GET_SINGLE(BoardManager)->GetCurrentPlayer();
}