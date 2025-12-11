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
#include <chrono>

SpamCard::SpamCard() : curPlayer(StoneType::NONE), spamUsed(false)
{
}

void SpamCard::Update()
{
	if (!isSkill) return;
	if (curPlayer != GET_SINGLE(BoardManager)->GetCurrentPlayer()) //턴 바뀜
	{
		if (spamUsed) 
		{
			NextTurn();
			return;
		}
		for (int i = 0; i < 7; ++i)
		{
			wstring randTexKey = GET_SINGLE(ResourceManager)->GetSpamTexture();
			Texture* spamTex = GET_SINGLE(ResourceManager)->GetTexture(randTexKey);
			Vec2 screenSize = Vec2(GetSystemMetrics(SM_CXSCREEN) - 400, GetSystemMetrics(SM_CYSCREEN) - 400);
			Vec2 randPos = Vec2((float)(rand() % (int)screenSize.x), (float)(rand() % (int)screenSize.y));
			Vec2 textureSize = Vec2((float)spamTex->GetWidth() + 15, (float)spamTex->GetHeight() + 30);

			auto nowStamp = std::chrono::high_resolution_clock::now().time_since_epoch().count();
			std::wstring spamKey = std::wstring(L"Spam") + std::to_wstring(nowStamp + i);

			SpamWindow* spamWindow = new SpamWindow(GET_SINGLE(WindowManager)->GetHInstance(), spamKey, randPos, textureSize,L"스팸 광고");
			GET_SINGLE(WindowManager)->AddWindow(spamWindow);

			SpamImage* spamImage = new SpamImage(spamTex);
			spamWindow->AddObject(spamImage);
			GET_SINGLE(SceneManager)->GetCurScene()->RequestSpawn(spamImage, Layer::UI);
			spamImage->SetWindowType(spamKey);
			SpamCloseButton* closeButton = new SpamCloseButton(spamKey, { textureSize.x - 30.f, 20.f }, { 30.f,30.f });
			spamWindow->AddObject(closeButton);
			GET_SINGLE(SceneManager)->GetCurScene()->RequestSpawn(closeButton, Layer::BUTTON);
			closeButton->SetWindowType(spamKey);
		}
		spamUsed = true;
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