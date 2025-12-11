#include "pch.h"
#include "StopMusicCard.h"
#include "ResourceManager.h"

StopMusicCard::StopMusicCard()
{
}
StopMusicCard::~StopMusicCard()
{
}

void StopMusicCard::CardSkill()
{
	GET_SINGLE(ResourceManager)->Stop(SOUND_CHANNEL::BGM);
	GET_SINGLE(ResourceManager)->Stop(SOUND_CHANNEL::EFFECT);
	GET_SINGLE(ResourceManager)->Stop(SOUND_CHANNEL::END);

	GET_SINGLE(ResourceManager)->Play(L"StopMusicEffect");
}