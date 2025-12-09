#pragma once
#include "Card.h"
class SpamCard :
    public Card
{
    public:
    SpamCard();
	~SpamCard() = default;
    public:
    virtual void Update() override;
    public:
    virtual void CardSkill() override;
	virtual void NextTurn() override;

private:
	StoneType curPlayer;
	bool spamUsed;
};

