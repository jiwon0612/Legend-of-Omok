#include "pch.h"
#include "Card.h"
#include "EarthquakeCard.h"
#include "IndiaInkCard.h"

Card::Card()
	: cardName(L""), explanation(L""), cardType(CardType::None)
{
}

Card::~Card()
{
}

void Card::Update()
{
}

void Card::Render(HDC _hdc)
{
	//카드 객체 그리기
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
}

//다음 턴시 카드 실행 정지 (몇 몇만)
void Card::NextTurn()
{
	isSkill = false;
}
