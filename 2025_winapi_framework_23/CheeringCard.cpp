#include "pch.h"
#include "CheeringCard.h"

CheeringCard::CheeringCard() : isDont(false), curNum(0), 

cheerText{
    L"멋지다! 화이팅!",
    L"잘 하고 계셔요!",
    L"당신은\n이 게임의 승자입니다!",
    L"실력이 황홀하시네요.",
    L"다음 수도 기대 됩니다!"
}
{
}

CheeringCard::~CheeringCard()
{
}

void CheeringCard::ReallySkill()
{
    isDont = true;
    GET_SINGLE(ResourceManager)->Play(L"CheeringEffect");
}
void CheeringCard::NextTurn()
{
    isSkill = false;
    isDont = false;
}

void CheeringCard::Update()
{
    if (!isSkill) return;

    if (!isDont &&
        curPlayer != GET_SINGLE(BoardManager)->GetCurrentPlayer()) //턴 바뀜
    {
        ReallySkill();
    }

    if (!isDont) return;

    if (curPlayer == GET_SINGLE(BoardManager)->GetCurrentPlayer()) //턴 바뀜
    {
        NextTurn();
        return;
    }
}
void CheeringCard::Render(HDC _hdc)
{
    if (!isDont) return;

    SetBkMode(_hdc, TRANSPARENT);
    SetTextColor(_hdc, RGB(0, 0, 0));

    HFONT fontSet = CreateFont(
        60, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
        DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
        ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_SWISS, L"맑은 고딕"
    );
    HFONT font = (HFONT)SelectObject(_hdc, fontSet);

	wstring curText = cheerText[curNum];

    for (int i = 1; i <= 4; ++i)
    {
        //RECT rect = { 0, WINDOW_HEIGHT / 2 + 200 -(i*100), WINDOW_WIDTH, WINDOW_HEIGHT / 2 + 300 - (i * 100) };
        RECT rect = { 0,150 - (i * 100), WINDOW_WIDTH, WINDOW_HEIGHT / 2 + 300 - (i * 100) };

        DrawText(_hdc, curText.c_str(), -1, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    }
}

void CheeringCard::CardSkill()
{
    isDont = false;
    isSkill = true;
    curPlayer = GET_SINGLE(BoardManager)->GetCurrentPlayer();

    int count = sizeof(cheerText) / sizeof(cheerText[0]);
    curNum = rand() % count;
}