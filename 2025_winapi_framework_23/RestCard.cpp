#include "pch.h"
#include "RestCard.h"
#include "BoardManager.h"

RestCard::RestCard()
{
	isSkill = false;
}
void RestCard::CardSkill()
{
	GET_SINGLE(BoardManager)->ResetGame();
	isSkill = true;
}
