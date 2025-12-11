#include "pch.h"
#include "CreditsCard.h"


CreditsCard::CreditsCard() : isDont(false),
cheerText{
    L"20311 ¡§øπ¿∫",
    L"20314 √÷¡ˆø¯",
    L"20315 √÷¬˘»£"
}
{
}

CreditsCard::~CreditsCard()
{
}

void CreditsCard::ReallySkill()
{
    isDont = true;
}
void CreditsCard::NextTurn()
{
    isSkill = false;
    isDont = false;
}

void CreditsCard::Update()
{
    if (!isSkill) return;

    if (!isDont &&
        curPlayer != GET_SINGLE(BoardManager)->GetCurrentPlayer()) //≈œ πŸ≤Ò
    {
        ReallySkill();
    }

    if (!isDont) return;

    if (curPlayer == GET_SINGLE(BoardManager)->GetCurrentPlayer()) //≈œ πŸ≤Ò
    {
        NextTurn();
        return;
    }
}
void CreditsCard::Render(HDC _hdc)
{
    if (!isDont && !isSkill) return;

    SetBkMode(_hdc, TRANSPARENT);
    SetTextColor(_hdc, RGB(0, 0, 0));

    HFONT fontSet = CreateFont(
        60, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
        DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
        ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_SWISS, L"∏º¿∫ ∞ÌµÒ"
    );
    HFONT font = (HFONT)SelectObject(_hdc, fontSet);

    for (int i = 0; i < 3; ++i)
    {
        RECT rect = { 0,-100+(i * 100), WINDOW_WIDTH, WINDOW_HEIGHT / 2 + 100 + (i * 100) };
        DrawText(_hdc, cheerText[i].c_str(), -1, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

        rect = { 0,-400 + (i * 100), WINDOW_WIDTH, WINDOW_HEIGHT / 2 + -200 + (i * 100) };
        DrawText(_hdc, cheerText[i].c_str(), -1, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

        rect = { 450,-100+(i * 100), WINDOW_WIDTH + 150, WINDOW_HEIGHT / 2 + 100 + (i * 100) };
        DrawText(_hdc, cheerText[i].c_str(), -1, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

        rect = { 450,-400 + (i * 100), WINDOW_WIDTH + 150 , WINDOW_HEIGHT / 2 + -200 + (i * 100) };
        DrawText(_hdc, cheerText[i].c_str(), -1, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

        rect = { -500,-100+(i * 100), WINDOW_WIDTH - 100, WINDOW_HEIGHT / 2 + 100 + (i * 100) };
        DrawText(_hdc, cheerText[i].c_str(), -1, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

        rect = { -500,-400 + (i * 100), WINDOW_WIDTH - 100, WINDOW_HEIGHT / 2 + -200 + (i * 100) };
        DrawText(_hdc, cheerText[i].c_str(), -1, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    }
}

void CreditsCard::CardSkill()
{
    isDont = false;
    isSkill = true;
    curPlayer = GET_SINGLE(BoardManager)->GetCurrentPlayer();
    GET_SINGLE(ResourceManager)->Play(L"CreditsEffect");

    int count = sizeof(cheerText) / sizeof(cheerText[0]);
}