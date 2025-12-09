#pragma once
#include "Card.h"

class SayHiCard
	: public Card
{
public:
	SayHiCard();
	~SayHiCard();
public:
	void Update() override;
	void Render(HDC _hdc) override;
public:
	void CardSkill();
private:
	void ReallySkill();
private:
	bool isDont;
};