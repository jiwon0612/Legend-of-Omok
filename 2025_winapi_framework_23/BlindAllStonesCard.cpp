#include "pch.h"
#include "BlindAllStonesCard.h"
#include "BoardManager.h"

BlindAllStonesCard::BlindAllStonesCard()
{
}

BlindAllStonesCard::~BlindAllStonesCard()
{
}

void BlindAllStonesCard::NextTurn()
{
	if (isSkill)
	{
		GET_SINGLE(BoardManager)->GetBoard()->SetBlindAllStones(true);
		isSkill = false;
	}
}

void BlindAllStonesCard::Update()
{

    if (!isSkill) return;

    if (curPlayer != GET_SINGLE(BoardManager)->GetCurrentPlayer()) //턴 바뀜
    {
        NextTurn();
        return;
    }
}

void BlindAllStonesCard::CardSkill()
{
	isSkill = true;
	curPlayer = GET_SINGLE(BoardManager)->GetCurrentPlayer();
}

