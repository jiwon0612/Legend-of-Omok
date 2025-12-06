#include "pch.h"
#include "PeaceCard.h"
#include "CardManager.h"

PeaceCard::PeaceCard() : isPeace(false)
{
}
PeaceCard::~PeaceCard()
{
}
void PeaceCard::ReallySkill()
{
    isPeace = true;
	GET_SINGLE(CardManager)->CardDelete();
}
void PeaceCard::NextTurn()
{
    isPeace = false;
    isSkill = false;
    GET_SINGLE(CardManager)->CardDelete();
}

void PeaceCard::Update()
{
    if (!isSkill) return;
    if (!isPeace &&
        curPlayer != GET_SINGLE(BoardManager)->GetCurrentPlayer()) //ÅÏ ¹Ù²ñ
    {
        ReallySkill();
    }

    if (!isPeace) return;

    if (isPeace &&
        curPlayer == GET_SINGLE(BoardManager)->GetCurrentPlayer()) //ÅÏ ¹Ù²ñ
    {
        NextTurn();
        return;
    }
}

void PeaceCard::Render(HDC _hdc)
{
    if (!isSkill) return;
}

void PeaceCard::CardSkill()
{
    isSkill = true;
    curPlayer = GET_SINGLE(BoardManager)->GetCurrentPlayer();
}