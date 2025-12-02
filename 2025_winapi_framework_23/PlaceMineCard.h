#pragma once
#include "Card.h"
class PlaceMineCard :
    public Card
{
public:
	PlaceMineCard();
	~PlaceMineCard();

public:
	virtual void Update() override;
	virtual void Render(HDC _hdc) override;
public:
	virtual void CardSkill();
	virtual void NextTurn();
};

