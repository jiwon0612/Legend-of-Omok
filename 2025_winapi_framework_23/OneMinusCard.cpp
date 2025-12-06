#include "pch.h"
#include "OneMinusCard.h"
#include "CardManager.h"

OneMinusCard::OneMinusCard() : isBlind(false)
{
}

OneMinusCard::~OneMinusCard()
{
}

void OneMinusCard::ReallySkill()
{
    isBlind = true;
    GET_SINGLE(CardManager)->ShowCard(GET_SINGLE(CardManager)
        ->GetShowCardCnt() - 1, curPlayer);
}

void OneMinusCard::NextTurn()
{
    isBlind = false;
    isSkill = false;
}

void OneMinusCard::Update()
{
    if (!isSkill) return;

    if (!isBlind &&
        curPlayer != GET_SINGLE(BoardManager)->GetCurrentPlayer()) //ÅÏ ¹Ù²ñ
    {
        ReallySkill();
    }

    if (!isBlind) return;

    if (curPlayer == GET_SINGLE(BoardManager)->GetCurrentPlayer()) //ÅÏ ¹Ù²ñ
    {
        NextTurn();
        return;
    }
}
void OneMinusCard::Render(HDC _hdc)
{
    if (!isSkill) return;
}

void OneMinusCard::CardSkill()
{
    isSkill = true;
    curPlayer = GET_SINGLE(BoardManager)->GetCurrentPlayer();
}