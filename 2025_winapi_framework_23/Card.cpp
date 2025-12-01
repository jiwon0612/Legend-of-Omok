#include "pch.h"
#include "Card.h"

Card::Card()
	: cardName(L""), explanation(L""), cardType(CardType::None)
	, curPlayer(StoneType::NONE), isSkill(false)
{
}

Card::~Card()
{
}

void Card::Update()
{
	if (!isSkill) return;
}

void Card::Render(HDC _hdc)
{
	if (!isSkill) return;
}

//카드 실행
void Card::CardSkill()
{
	isSkill = true;
	curPlayer = GET_SINGLE(BoardManager)->GetCurrentPlayer();
}

void Card::NextTurn()
{
	isSkill = false;
}
