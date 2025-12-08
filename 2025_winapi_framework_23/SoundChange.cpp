#include "pch.h"
#include "SoundChange.h"
#include "ResourceManager.h"

SoundChange::SoundChange()
{
}
SoundChange::~SoundChange()
{
}

void SoundChange::CardSkill()
{
	GET_SINGLE(ResourceManager)->Stop(SOUND_CHANNEL::BGM);

	int num = (rand()% 2)+1;
	wstring key = L"BGM_0" + std::to_wstring(num);

	GET_SINGLE(ResourceManager)->Play(key);
}