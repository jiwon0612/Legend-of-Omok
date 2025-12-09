#include "pch.h"
#include "SpamCard.h"
#include "SubWindow.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "WindowManager.h"
#include "Texture.h"
#include "SpamImage.h"
#include "SpamWindow.h"
#include "SpamCloseButton.h"

SpamCard::SpamCard() : curPlayer(StoneType::NONE), spamUsed(false)
{
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
			SpamWindow* spamWindow = new SpamWindow(GET_SINGLE(WindowManager)->GetHInstance(), {L"Spam"+i}, randPos, textureSize);
			GET_SINGLE(WindowManager)->AddWindow(spamWindow);

			SpamImage* spamImage = new SpamImage(spamTex);
			spamWindow->AddObject(spamImage);
			GET_SINGLE(SceneManager)->GetCurScene()->AddObject(spamImage, Layer::UI);
			SpamCloseButton* closeButton = new SpamCloseButton({ L"Spam" + i }, { textureSize.x - 30.f, 0.f }, { 30.f,30.f });
			spamWindow->AddObject(closeButton);
			GET_SINGLE(SceneManager)->GetCurScene()->AddObject(closeButton, Layer::UI);
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
