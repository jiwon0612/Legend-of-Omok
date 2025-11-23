#pragma once
#include "Object.h"

enum class CardType
{
	None = 0,
	Disturbanc, //방해 (먹물 뿌리기...)
	Etc, //기타 (노래변경...)
	Active,
};

class Card : 
	public Object
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
private:
	wstring cardName;
	wstring explanation;
	CardType cardType;
};