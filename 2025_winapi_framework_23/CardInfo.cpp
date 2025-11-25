#include "pch.h"
#include "CardInfo.h"

CardInfo::CardInfo(wstring _name, wstring _description, wstring _iconName, CardRarity _rarity)
{
	name = _name;
	description = _description;
	iconName = _iconName;
	cardRarity = _rarity;
}

CardInfo::~CardInfo()
{
}
