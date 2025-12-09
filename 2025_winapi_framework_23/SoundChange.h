#pragma once
#include "Card.h"

class SoundChange
	: public Card
{
public:
	SoundChange();
	~SoundChange();
public:
	void CardSkill();
private:
	int soundNum = 3;
};

