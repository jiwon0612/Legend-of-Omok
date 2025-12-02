#include "pch.h"
#include "BlindAllStonesCard.h"
#include "BoardManager.h"

BlindAllStonesCard::BlindAllStonesCard()
{
}

BlindAllStonesCard::~BlindAllStonesCard()
{
}

void BlindAllStonesCard::CardSkill()
{
	isSkill = true;
}

void BlindAllStonesCard::NextTurn()
{
	if (isSkill)
	{
		GET_SINGLE(BoardManager)->BlindAllStonesSkill();
		isSkill = false;
	}
}
