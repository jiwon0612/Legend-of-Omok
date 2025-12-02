#pragma once
#include "Card.h"
class BlindAllStonesCard :
    public Card
{
    public:
    BlindAllStonesCard();
	virtual ~BlindAllStonesCard();
    public:
		virtual void CardSkill() override;
		virtual void NextTurn() override;
};

