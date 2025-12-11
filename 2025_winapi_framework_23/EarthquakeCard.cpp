#include "pch.h"
#include "EarthquakeCard.h"
#include "Core.h"

EarthquakeCard::EarthquakeCard()
	:isShake(false)
	, _timer(0)
	, _shakeSpeed(0.01f)
	, _isShakeMove(false)
	, _isShakeStart(false)
	, _startPos(0, 0)
{
}

EarthquakeCard::~EarthquakeCard()
{
}

void EarthquakeCard::ReallySkill()
{
	isShake = true;
	_isShakeStart = false;
	GET_SINGLE(ResourceManager)->Play(L"EarthquakeEffect");
	GET_SINGLE(ResourceManager)->Volume(SOUND_CHANNEL::EFFECT, 1);
}
void EarthquakeCard::NextTurn()
{
	isShake = false;
	isSkill = false;
}

void EarthquakeCard::Update()
{
	if (!isSkill) return;

	if (!isShake &&
		curPlayer != GET_SINGLE(BoardManager)->GetCurrentPlayer()) //≈œ πŸ≤Ò
	{
		ReallySkill();
	}

	if (!isShake) return;

	if (isShake &&
		curPlayer == GET_SINGLE(BoardManager)->GetCurrentPlayer()) //≈œ πŸ≤Ò
	{
		NextTurn();
	}
}

void EarthquakeCard::ShakeWindow(HWND hWnd, int durationMs, int strength)
{
	_timer += fDT;
	

	if (_timer <= _shakeSpeed)
	{
		return;
	}

	_timer = 0;

	RECT rect;
	GetWindowRect(hWnd, &rect);

	int x = rect.left;
	int y = rect.top;

	if (!_isShakeStart)
	{
		_startPos = { (float)x, (float)y };
		_isShakeStart = true;
	}

	//auto start = GetTickCount();

	//while (GetTickCount() - start < durationMs)
	//{

	//	//Sleep(16);
	//}

	int offsetX = (rand() % (strength * 2)) - strength;
	int offsetY = (rand() % (strength * 2)) - strength;

	if (!_isShakeMove)
	{
		SetWindowPos(hWnd, NULL, x + offsetX, y + offsetY, 0, 0,
			SWP_NOSIZE | SWP_NOZORDER | SWP_NOREDRAW);
	}
	else
	{
		SetWindowPos(hWnd, NULL, _startPos.x, _startPos.y, 0, 0,
			SWP_NOSIZE | SWP_NOZORDER | SWP_NOREDRAW);
	}
	_isShakeMove = !_isShakeMove;
}

void EarthquakeCard::Render(HDC _hdc)
{
	if (!isSkill) return;
	if (!isShake) return;
	ShakeWindow(GET_SINGLE(Core)->GetHwnd(), 500, 50);
}
void EarthquakeCard::CardSkill()
{
	isSkill = true;
	curPlayer = GET_SINGLE(BoardManager)->GetCurrentPlayer();
}