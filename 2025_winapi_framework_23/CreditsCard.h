#pragma once
#include "Card.h"
class CreditsCard :
    public Card
{
public:
	CreditsCard();
	~CreditsCard();
public:
	void Update() override;
	void Render(HDC _hdc) override;
public:
	void CardSkill();
private:
	void ReallySkill();
	void NextTurn();
private:
	bool isDont;
	wstring cheerText[3];
};

