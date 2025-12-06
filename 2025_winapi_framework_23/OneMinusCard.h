#pragma once
#include "Card.h"

class OneMinusCard
	: public Card
{
public:
	OneMinusCard();
	~OneMinusCard();
public:
	void Update() override;
	void Render(HDC _hdc) override;
public:
	void CardSkill();
	void NextTurn();
private:
	void ReallySkill();
private:
	bool isBlind;
};

