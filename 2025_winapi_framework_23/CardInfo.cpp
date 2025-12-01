#include "pch.h"
#include "CardInfo.h"

CardInfo::CardInfo(wstring _name, wstring _description, wstring _iconName, CardRarity _rarity, Card* _card)
{
	name = _name;
	description = _description;
	iconName = _iconName;
	cardRarity = _rarity;
	card = _card;
}

CardInfo::~CardInfo()
{
	SAFE_DELETE(card);
}
