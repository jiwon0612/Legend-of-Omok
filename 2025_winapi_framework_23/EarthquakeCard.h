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
	void CardSkill();
	void NextTurn();
private:
	void ReallySkill();
	void ShakeWindow(HWND hWnd, int durationMs, int strength);
private:
	bool isShake;
	float _timer;
	float _shakeSpeed;
	bool _isShakeMove;
	Vector2 _startPos;
	bool _isShakeStart;
};