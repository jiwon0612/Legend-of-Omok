#pragma once
#include "Card.h"

class TimeStopCard
	: public Card
{
public:
	TimeStopCard();
	~TimeStopCard();
public:
	void Update() override;
	void Render(HDC _hdc) override;
public:
	void CardSkill();
};