#include "pch.h"
#include "Card.h"
#include "Board.h"

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
void Card::SetCard(wstring name, wstring explanation, CardType type)
{
	cardName = name;
	this->explanation = explanation;
	cardType = type;
}

//카드 실행
void Card::CardSkill()
{
	isSkill = true;
	curPlayer = Board::GetInstance()->GetCurrentPlayer();
}

void Card::NextTurn()
{
	isSkill = false;
}
