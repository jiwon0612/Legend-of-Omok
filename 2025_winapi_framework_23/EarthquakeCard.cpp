#include "pch.h"
#include "EarthquakeCard.h"


EarthquakeCard::EarthquakeCard():isShake(false)
{
}

EarthquakeCard::~EarthquakeCard()
{
}

void EarthquakeCard::ReallySkill()
{
    isShake = true;
}
void EarthquakeCard::NextTurn()
{
    isShake = false;
    Card::NextTurn();
}

void EarthquakeCard::Update()
{
    Card::Update();

    if (!isShake &&
        curPlayer != GET_SINGLE(BoardManager)->GetCurrentPlayer()) //≈œ πŸ≤Ò
    {
        ReallySkill();
    }

    if (!isShake) return;

    if (!isShake &&
        curPlayer == GET_SINGLE(BoardManager)->GetCurrentPlayer()) //≈œ πŸ≤Ò
    {
        NextTurn();
    }
}

void EarthquakeCard::ShakeWindow(HWND hWnd, int durationMs, int strength)
{
    RECT rect;
    GetWindowRect(hWnd, &rect);

    int x = rect.left;
    int y = rect.top;

    auto start = GetTickCount();

    while (GetTickCount() - start < durationMs)
    {
        int offsetX = (rand() % (strength * 2)) - strength;
        int offsetY = (rand() % (strength * 2)) - strength;

        SetWindowPos(hWnd, NULL, x + offsetX, y + offsetY, 0, 0,
            SWP_NOSIZE | SWP_NOZORDER | SWP_NOREDRAW);

        Sleep(16);
    }

    SetWindowPos(hWnd, NULL, x, y, 0, 0,
        SWP_NOSIZE | SWP_NOZORDER | SWP_NOREDRAW);
}

void EarthquakeCard::Render(HDC _hdc)
{
    Card::Render(_hdc);
    if (!isShake) return;
    ShakeWindow(GetActiveWindow(), 500, 50);
}
void EarthquakeCard::SetCard(wstring name, wstring explanation, CardType type)
{
    Card::SetCard(name, explanation, type);
}
void EarthquakeCard::CardSkill()
{
    Card::CardSkill();
}