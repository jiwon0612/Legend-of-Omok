#pragma once
#include "Card.h"
class BlindAllStonesCard :
    public Card
{
public:
    BlindAllStonesCard();
	virtual ~BlindAllStonesCard();
	virtual void Update() override;
public:
	virtual void CardSkill() override;
	virtual void NextTurn() override;
private:
	bool isBlind;
};