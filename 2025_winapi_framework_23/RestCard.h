#pragma once
#include "Card.h"
class RestCard :
    public Card
{
    public:
    RestCard();
	~RestCard() = default;
    public:
		virtual void CardSkill() override;
};

