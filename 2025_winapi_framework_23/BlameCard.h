#pragma once
#include "Card.h"

class BlameCard:
	public Card
{
public:
	BlameCard();
	~BlameCard();
public:
	void Update() override;
	void Render(HDC _hdc) override;
public:
	void CardSkill();
private:
	void ReallySkill();
	void NextTurn();
private:
	bool isDont;
	int curNum;
	wstring blameText[5];
};

