#include "pch.h"
#include "SpamCard.h"
#include "SubWindow.h"
#include "SceneManager.h"

SpamCard::SpamCard()
{
	isSkill = false;
}

void SpamCard::Update()
{ 
	if (!isSkill) return;
}

void SpamCard::CardSkill()
{
	isSkill = true;
}

void SpamCard::NextTurn()
{
}
