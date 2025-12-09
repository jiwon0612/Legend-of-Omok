#include "pch.h"
#include "SpamCard.h"
#include "SubWindow.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "WindowManager.h"
#include "Texture.h"
#include "SpamImage.h"

SpamCard::SpamCard() : curPlayer(StoneType::NONE), spamUsed(false)
{
	isSkill = false;
	spamUsed = false;
}

void SpamCard::Update()
{ 
	if (!isSkill) return;
    if (curPlayer != GET_SINGLE(BoardManager)->GetCurrentPlayer()) //턴 바뀜
    {
		for (int i = 0; i < 7; ++i)
		{
			wstring randTexKey = GET_SINGLE(ResourceManager)->GetSpamTexture();
			Texture* spamTex = GET_SINGLE(ResourceManager)->GetTexture(randTexKey);
			Vec2 screenSize = Vec2(GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));
			Vec2 randPos = Vec2((float)(rand() % (int)screenSize.x), (float)(rand() % (int)screenSize.y));
			Vec2 textureSize = Vec2((float)spamTex->GetWidth(), (float)spamTex->GetHeight());
			SubWindow* spamWindow = new SubWindow(GET_SINGLE(WindowManager)->GetHInstance(), {L"Spam"+i}, randPos, textureSize);

			SpamImage* spamImage = new SpamImage(spamTex);
			//spamWindow->AddObject(spamImage, Layer::BACKGROUND);
		}
		spamUsed = true;
    }

    if (!spamUsed) return;

    if (curPlayer == GET_SINGLE(BoardManager)->GetCurrentPlayer()) //턴 바뀜
    {
        NextTurn();
    }
}

void SpamCard::CardSkill()
{
	curPlayer = GET_SINGLE(BoardManager)->GetCurrentPlayer();
	isSkill = true;
}

void SpamCard::NextTurn()
{
	isSkill = false;
	spamUsed = false;
}
