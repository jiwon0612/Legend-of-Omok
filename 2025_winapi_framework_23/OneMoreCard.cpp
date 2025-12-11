#include "pch.h"
#include "OneMoreCard.h"

OneMoreCard::OneMoreCard() : isMore(false)
{
}
OneMoreCard::~OneMoreCard()
{
}
void OneMoreCard::ReallySkill()
{
    isMore = true;
    GET_SINGLE(BoardManager)->GetBoard()->SwitchTurn();
    GET_SINGLE(ResourceManager)->Play(L"OneMoreEffect");
    GET_SINGLE(ResourceManager)->Volume(SOUND_CHANNEL::EFFECT, 1);
}
void OneMoreCard::NextTurn()
{
    isMore = false;
    isSkill = false;
}

void OneMoreCard::Update()
{
    if (!isSkill) return;
    if (!isMore &&
        curPlayer != GET_SINGLE(BoardManager)->GetCurrentPlayer()) //ÅÏ ¹Ù²ñ
    {
        ReallySkill();
    }

    if (!isMore) return;

    if (isMore &&
        curPlayer == GET_SINGLE(BoardManager)->GetCurrentPlayer()) //ÅÏ ¹Ù²ñ
    {
        NextTurn();
        return;
    }
}

void OneMoreCard::Render(HDC _hdc)
{
    if (!isSkill) return;
}

void OneMoreCard::CardSkill()
{
    isSkill = true;
    curPlayer = GET_SINGLE(BoardManager)->GetCurrentPlayer();
}