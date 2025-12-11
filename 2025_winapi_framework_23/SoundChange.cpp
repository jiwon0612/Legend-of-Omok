#include "pch.h"
#include "SoundChange.h"
#include "ResourceManager.h"

SoundChange::SoundChange() : soundNum(3)
{
}
SoundChange::~SoundChange()
{
}

void SoundChange::CardSkill()
{
	GET_SINGLE(ResourceManager)->Stop(SOUND_CHANNEL::BGM);

	int num = (rand()% soundNum)+1;
	wstring key = L"BGM_0" + std::to_wstring(num);

	GET_SINGLE(ResourceManager)->Play(key);
	GET_SINGLE(ResourceManager)->Volume(SOUND_CHANNEL::BGM, 0.5);
}