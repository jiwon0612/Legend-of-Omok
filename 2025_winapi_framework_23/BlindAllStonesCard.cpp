#include "pch.h"
#include "BlindAllStonesCard.h"
#include "BoardManager.h"

BlindAllStonesCard::BlindAllStonesCard() : isBlind(false)
{
}

BlindAllStonesCard::~BlindAllStonesCard()
{
}

void BlindAllStonesCard::NextTurn()
{
    isBlind = false;
    isSkill = false;
}

void BlindAllStonesCard::Update()
{
    if (!isSkill) return;

    if (curPlayer != GET_SINGLE(BoardManager)->GetCurrentPlayer()) //턴 바뀜
    {
        isBlind = true;
        GET_SINGLE(BoardManager)->GetBoard()->SetBlindAllStones(true); //가리기
    }

    if (!isBlind) return;

    if (curPlayer == GET_SINGLE(BoardManager)->GetCurrentPlayer()) //턴 바뀜
    {
        NextTurn();
    }
}

void BlindAllStonesCard::CardSkill()
{
	isSkill = true;
	curPlayer = GET_SINGLE(BoardManager)->GetCurrentPlayer();
}