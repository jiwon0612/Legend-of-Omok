#pragma once
#include "Card.h"

class StopMusicCard
	: public Card
{
public:
	StopMusicCard();
	~StopMusicCard();
public:
	void CardSkill();
};