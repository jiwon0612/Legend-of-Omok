#include "pch.h"
#include "CardTestScene.h"
#include "Object.h"
#include "CardInfo.h"
#include "CardUI.h"
#include "CardManager.h"
#include "InputManager.h"

void CardTestScene::Init()
{
	CardInfo* testCard1 = new CardInfo(L"TestName", L"TestDescription",
		L"Bullet", CardRarity::Normal);

	CardUI* cardUI = Spawn<CardUI>(Layer::UI, { 200.f, 200.f }, { 100.f,150.f });
	cardUI->Init(testCard1);

}

void CardTestScene::Update()
{
	Scene::Update();
	if (GET_KEYDOWN(KEY_TYPE::T))
	{
		GET_SINGLE(CardManager)->ShowCard(5);
	}
}

void CardTestScene::Render(HDC _hdc)
{
	Scene::Render(_hdc);
}
