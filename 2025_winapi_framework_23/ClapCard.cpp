#include "pch.h"
#include "ClapCard.h"
#include "ResourceManager.h"

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