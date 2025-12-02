#include "pch.h"
#include "TimeStopCard.h"

TimeStopCard::TimeStopCard()
{
}
TimeStopCard::~TimeStopCard()
{
}

void TimeStopCard::Update()
{
    if (!isSkill) return;
}

void TimeStopCard::Render(HDC _hdc)
{
    if (!isSkill) return;
}

void TimeStopCard::CardSkill()
{
    isSkill = true;
    curPlayer = GET_SINGLE(BoardManager)->GetCurrentPlayer();
    GET_SINGLE(BoardManager)->TimeStopSkill();
    isSkill = false;
}