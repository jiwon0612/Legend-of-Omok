#pragma once
#include "Object.h"

class Card : public Object
{
public:
	Card();
	~Card();
public:
	virtual void Update() override;
	virtual void Render(HDC _hdc) override;
public:
	virtual void SetCard(wstring name, wstring explanation, CardType type);
	virtual void CardSkill();
	virtual void NextTurn();
protected:
	wstring cardName;
	wstring explanation;
	CardType cardType;
protected:
	bool isSkill;
};