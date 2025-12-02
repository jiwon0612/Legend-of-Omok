#include "pch.h"
#include "PlaceMineCard.h"
#include "BoardManager.h"

PlaceMineCard::PlaceMineCard()
{
}
PlaceMineCard::~PlaceMineCard()
{
}

void PlaceMineCard::Update()
{
	if (!isSkill) return;
}

void PlaceMineCard::Render(HDC _hdc)
{
	if (!isSkill) return;
}

void PlaceMineCard::CardSkill()
{
	isSkill = true;
	GET_SINGLE(BoardManager)->ActivateMineSkill();
}

void PlaceMineCard::NextTurn()
{
}
