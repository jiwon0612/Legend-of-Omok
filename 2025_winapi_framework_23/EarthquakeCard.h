#pragma once
#include "Card.h"

class EarthquakeCard
	: Card
{
	public:
	EarthquakeCard();
	~EarthquakeCard();
public:
	void Update() override;
	void Render(HDC _hdc) override;
public:
	void SetCard(wstring name, wstring explanation, CardType type);
	void CardSkill();
};