#include "pch.h"
#include "SayHiCard.h"

SayHiCard::SayHiCard() : isDont(false)
{
}

SayHiCard::~SayHiCard()
{
}

void SayHiCard::ReallySkill()
{
	isDont = true;
    isSkill = false;
}

void SayHiCard::Update()
{
    if (!isSkill) return;

    if (!isDont &&
        curPlayer != GET_SINGLE(BoardManager)->GetCurrentPlayer()) //ÅÏ ¹Ù²ñ
    {
        ReallySkill();
    }
}
void SayHiCard::Render(HDC _hdc)
{
    if (!isSkill) return;

    SetBkMode(_hdc, TRANSPARENT);
    SetTextColor(_hdc, RGB(rand()%256, rand() % 256, rand() % 256));

    HFONT fontSet = CreateFont(
        130, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
        DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
        ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_SWISS, L"¸¼Àº °íµñ"
    );
    HFONT font = (HFONT)SelectObject(_hdc, fontSet);

    //RECT rect = { 0, WINDOW_HEIGHT / 2 - 100, WINDOW_WIDTH, WINDOW_HEIGHT / 2 +100};
    RECT rect = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
    DrawText(_hdc, L"¾È³çÇÏ¼¼¿ä!", -1, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}

void SayHiCard::CardSkill()
{
    isDont = false;
    isSkill = true;
    curPlayer = GET_SINGLE(BoardManager)->GetCurrentPlayer();
    GET_SINGLE(ResourceManager)->Play(L"SayHiEffect");
}