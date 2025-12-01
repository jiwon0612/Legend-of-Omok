#include "pch.h"
#include "DeleteTimeCard.h"

DeleteTimeCard::DeleteTimeCard()
{
}
DeleteTimeCard::~DeleteTimeCard()
{
}

void DeleteTimeCard::Update()
{
    Card::Update();
}

void DeleteTimeCard::Render(HDC _hdc)
{
    Card::Render(_hdc);
}

void DeleteTimeCard::SetCard(wstring name, wstring explanation, CardType type)
{
    Card::SetCard(name, explanation, type);
}
void DeleteTimeCard::CardSkill()
{
    Card::CardSkill();
    curPlayer = (curPlayer != StoneType::BLACK) ? StoneType::BLACK : StoneType::WHITE; //상대 돌로 바꾸기

    GET_SINGLE(BoardManager)->SetPlayerTime(curPlayer,
        GET_SINGLE(BoardManager)->GetPlayerTime(curPlayer) - 20); //20초 감소
    isSkill = false;
}