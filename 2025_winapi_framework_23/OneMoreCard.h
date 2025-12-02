#pragma once
#include "Card.h"
class OneMoreCard
	: public Card
{
public:
	OneMoreCard();
	~OneMoreCard();
public:
	void Update() override;
	void Render(HDC _hdc) override;
public:
	void CardSkill();
};

