#include "pch.h"
#include "RerollCard.h"
#include "CardManager.h"

RerollCard::RerollCard()
{
}

RerollCard::~RerollCard()
{
}

void RerollCard::Update()
{
	if (!isSkill) return;
}

void RerollCard::Render(HDC _hdc)
{
	if (!isSkill) return;
}

void RerollCard::CardSkill()
{
	isSkill = false;
	curPlayer = GET_SINGLE(BoardManager)->GetCurrentPlayer();
	GET_SINGLE(CardManager)->ShowCard(GET_SINGLE(CardManager)->GetShowCardCnt(), curPlayer);
}
