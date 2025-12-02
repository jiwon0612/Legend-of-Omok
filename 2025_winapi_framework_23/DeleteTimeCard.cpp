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
    if (!isSkill) return;
}

void DeleteTimeCard::Render(HDC _hdc)
{
    if (!isSkill) return;
}

void DeleteTimeCard::CardSkill()
{
    isSkill = true;
    curPlayer = GET_SINGLE(BoardManager)->GetCurrentPlayer();

    curPlayer = (curPlayer != StoneType::BLACK) ? StoneType::BLACK : StoneType::WHITE; //상대 돌로 바꾸기

    GET_SINGLE(BoardManager)->SetPlayerTime(curPlayer,
        GET_SINGLE(BoardManager)->GetPlayerTime(curPlayer) - 20); //20초 감소
    isSkill = false;
}