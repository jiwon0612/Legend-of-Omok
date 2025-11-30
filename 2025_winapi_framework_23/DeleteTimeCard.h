#pragma once
#include "Card.h"

class DeleteTimeCard
	: public Card
{
public:
	DeleteTimeCard();
	~DeleteTimeCard();
public:
	void Update() override;
	void Render(HDC _hdc) override;
public:
	void SetCard(wstring name, wstring explanation, CardType type) override;
	void CardSkill();
};

