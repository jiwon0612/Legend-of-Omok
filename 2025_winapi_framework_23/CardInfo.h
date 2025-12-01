#pragma once

class Card;

class CardInfo
{
public:
	CardInfo(wstring _name, wstring _description, wstring _iconName, CardRarity _rarity, Card* _card);
	~CardInfo();
public:
	wstring name;
	wstring description;
	wstring iconName;
	CardRarity cardRarity;
	Card* card;
};

