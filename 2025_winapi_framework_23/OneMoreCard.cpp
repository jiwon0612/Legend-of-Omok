#include "pch.h"
#include "OneMoreCard.h"

OneMoreCard::OneMoreCard()
{
}
OneMoreCard::~OneMoreCard()
{
}

void OneMoreCard::Update()
{
    if (!isSkill) return;
}

void OneMoreCard::Render(HDC _hdc)
{
    if (!isSkill) return;
}

void OneMoreCard::CardSkill()
{
    isSkill = true;
    curPlayer = GET_SINGLE(BoardManager)->GetCurrentPlayer();
    GET_SINGLE(BoardManager)->GetBoard()->SwitchTurn();
    isSkill = false;
}