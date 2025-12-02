#pragma once
#include"Card.h"

class RerollCard : public Card
{
public:
	RerollCard();
	~RerollCard();
public:
	virtual void Update() override;
	virtual void Render(HDC _hdc) override;
public:
	virtual void CardSkill();
};

