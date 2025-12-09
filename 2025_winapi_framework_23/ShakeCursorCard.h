#pragma once
#include "Card.h"

class ShakeCursorCard
	: public Card
{
public:
	ShakeCursorCard();
	~ShakeCursorCard();
public:
	void Update() override;
	void Render(HDC _hdc) override;
public:
	void CardSkill();
	void NextTurn();
private:
	void ShakeCursor();
	void ReallySkill();
private:
	bool isBlind;
};

