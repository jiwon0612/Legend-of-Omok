#pragma once
#include "Card.h"

class CheeringCard :
    public Card
{
public:
	CheeringCard();
	~CheeringCard();
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
	int curNum;
	wstring cheerText[5];
};