#include "pch.h"
#include "ReplaceRandomStoneSkill.h"
#include "BoardManager.h"

ReplaceRandomStoneSkill::ReplaceRandomStoneSkill()
{
}

ReplaceRandomStoneSkill::~ReplaceRandomStoneSkill()
{
}

void ReplaceRandomStoneSkill::CardSkill()
{
	isSkill = true;
	GET_SINGLE(BoardManager)->GetBoard()->ReplaceRandomStone();
}
