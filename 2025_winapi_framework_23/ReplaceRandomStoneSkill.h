#pragma once
#include "Card.h"
class ReplaceRandomStoneSkill :
    public Card
{
    public:
    ReplaceRandomStoneSkill();
	~ReplaceRandomStoneSkill();
    public:
		virtual void CardSkill() override;
};

