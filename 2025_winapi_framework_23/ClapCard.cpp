#include "pch.h"
#include "ClapCard.h"
#include "ResourceManager.h"

//혹시 오류나서 왔다면...
//박수 소리는 아직 없으삼 ^ㅁ^;;
ClapCard::ClapCard()
{
}
ClapCard::~ClapCard()
{
}

void ClapCard::CardSkill()
{
	GET_SINGLE(ResourceManager)->Play(L"ClapEffect");
}