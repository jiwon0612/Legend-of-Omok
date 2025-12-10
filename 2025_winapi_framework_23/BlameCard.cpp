#include "pch.h"
#include "BlameCard.h"

BlameCard::BlameCard() : isDont(false), curNum(0),

blameText{
    L"그냥 접죠...?",
    L"에계?",
    L"진심이에요?\n실망이네요.",
    L"추잡해요! 관둬요!",
    L"지겹고, 따분해요."
}
{
}

BlameCard::~BlameCard()
{
}

void BlameCard::ReallySkill()
{
    isDont = true;
}
void BlameCard::NextTurn()
{
    isSkill = false;
    isDont = false;
}

void BlameCard::Update()
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
void BlameCard::Render(HDC _hdc)
{
    if (!isSkill || isDont) return;

    SetBkMode(_hdc, TRANSPARENT);
    SetTextColor(_hdc, RGB(0, 0, 0));

    HFONT fontSet = CreateFont(
        65, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
        DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
        ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_SWISS, L"맑은 고딕"
    );
    HFONT font = (HFONT)SelectObject(_hdc, fontSet);
    wstring curText = blameText[curNum];

    for(int i = 1; i <= 4; ++i)
    {
        //RECT rect = { 0, WINDOW_HEIGHT / 2 + 200 -(i*100), WINDOW_WIDTH, WINDOW_HEIGHT / 2 + 300 - (i * 100) };
        RECT rect = { 0,150 -(i*100), WINDOW_WIDTH, WINDOW_HEIGHT / 2 + 300 - (i * 100) };

        DrawText(_hdc, curText.c_str(), -1, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}
}

void BlameCard::CardSkill()
{
    isDont = false;
    isSkill = true;
    curPlayer = GET_SINGLE(BoardManager)->GetCurrentPlayer();

    int count = sizeof(blameText) / sizeof(blameText[0]);
    curNum = rand() % count;
}