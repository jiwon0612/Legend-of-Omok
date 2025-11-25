#include "pch.h"
#include "EarthquakeCard.h"


EarthquakeCard::EarthquakeCard() : isShaking(false)
{
}

EarthquakeCard::~EarthquakeCard()
{
}

void EarthquakeCard::Update()
{
}

void ShakeWindow(HWND hWnd, int durationMs, int strength)
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
    if (!isShaking) return;
    ShakeWindow(GetActiveWindow(), 500, 50);
}
void EarthquakeCard::SetCard(wstring name, wstring explanation, CardType type)
{
    cardName = name;
    this->explanation = explanation;
    cardType = type;
}
void EarthquakeCard::CardSkill()
{
	isShaking = true;
}