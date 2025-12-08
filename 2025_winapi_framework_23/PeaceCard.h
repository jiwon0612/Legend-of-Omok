#pragma once
#include "Card.h"

class PeaceCard
	: public Card
{
public:
	PeaceCard();
	~PeaceCard();
public:
	void Update() override;
	void Render(HDC _hdc) override;
public:
	void CardSkill();
	void NextTurn();
private:
	void ReallySkill();
private:
	bool isPeace;
};