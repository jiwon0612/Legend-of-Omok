#pragma once
#include "Card.h"

class EarthquakeCard
	: public Card
{
	public:
	EarthquakeCard();
	~EarthquakeCard();
public:
	void Update() override;
	void Render(HDC _hdc) override;
public:
	void SetCard(wstring name, wstring explanation, CardType type) override;
	void CardSkill();
	void NextTurn();
private:
	void ReallySkill();
	void ShakeWindow(HWND hWnd, int durationMs, int strength);
private:
	bool isShake;
};