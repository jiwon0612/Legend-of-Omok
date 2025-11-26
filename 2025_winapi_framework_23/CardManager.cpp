#include "pch.h"
#include "CardManager.h"
#include "CardInfo.h"
#include "SceneManager.h"
#include "CardUI.h"
#include "EarthquakeCard.h"
#include "IndiaInkCard.h"

void CardManager::Init()
{
	m_cardStartPos = { 1150.f, 525.f };
	m_cardPos = { 200.f, 525.f };
	m_cardOffset = { 200.f, 0.f };

	Card* card = GET_SINGLE(SceneManager)->GetCurScene()->Spawn<IndiaInkCard>(Layer::UI,m_cardStartPos,{ 100.f,150.f });
	CardInfo* testCard1 = new CardInfo(L"TestName", L"TestDescription",
		L"Bullet", CardRarity::Normal, card);

	m_cardInfoMap.insert({ testCard1->name, testCard1 });
}

void CardManager::ShowCard(int cnt)
{
	for (size_t i = 0; i < m_cardUIList.size(); i++)
	{
		GET_SINGLE(SceneManager)->GetCurScene()->RequestDestroy(m_cardUIList[i]);
	}

	for (int i = cnt - 1; i >= 0; i--)
	{
		CardUI* ui = GET_SINGLE(SceneManager)->GetCurScene()->Spawn<CardUI>(Layer::UI,
			m_cardStartPos,
			{ 100.f,150.f });
		m_cardUIList.push_back(ui);
		ui->Init(GetCardInfo(L"TestName"));
		ui->MoveToPosition(ui->GetPos(), m_cardPos + m_cardOffset * i);
	}
}
