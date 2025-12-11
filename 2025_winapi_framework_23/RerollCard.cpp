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
	isSkill = true;
	curPlayer = GET_SINGLE(BoardManager)->GetCurrentPlayer();

	GET_SINGLE(CardManager)->ShowCard(GET_SINGLE(CardManager)
		->GetShowCardCnt(), curPlayer);
	isSkill = false;
	GET_SINGLE(ResourceManager)->Play(L"RerollEffect");
	GET_SINGLE(ResourceManager)->Volume(SOUND_CHANNEL::EFFECT, 1);
}