#pragma once
class CardInfo
{
public:
	CardInfo(wstring _name, wstring _description, wstring _iconName, CardRarity _rarity);
	~CardInfo();
public:
	wstring name;
	wstring description;
	wstring iconName;
	CardRarity cardRarity;
	//사용 효과 클래스 
};

