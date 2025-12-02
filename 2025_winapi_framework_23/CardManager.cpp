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

	//Card* card = GET_SINGLE(SceneManager)->GetCurScene()->Spawn<IndiaInkCard>(Layer::UI, m_cardStartPos, { 100.f,150.f });
	//CardInfo* testCard1 = new CardInfo(L"TestName", L"TestDescription",
	//	L"Bullet", CardRarity::Normal, card);
	////m_cardInfoMap.insert({ testCard1->name, testCard1 });
	//m_cardInfoMap[testCard1->name] = testCard1;
	//m_cardKeyList[CardRarity::Normal].push_back(testCard1->name);

	RegisterCard<IndiaInkCard>(L"TestName", L"TestDescription", L"Bullet", CardRarity::Normal);
	
	m_cardKeyList[CardRarity::Rare].push_back(L"test");
	m_cardKeyList[CardRarity::Unique].push_back(L"test");
	m_cardKeyList[CardRarity::Legendary].push_back(L"test");

	m_showCardCnt = 1;
}

void CardManager::LateInit()
{
	

}

void CardManager::ShowCard(int cnt,StoneType _curType)
{
	for (size_t i = 0; i < m_cardUIList.size(); i++)
	{
		GET_SINGLE(SceneManager)->GetCurScene()->RequestDestroy(m_cardUIList[i]);
		//auto& c = m_cardUIList[i];
		//m_cardUIList.erase(std::remove(m_cardUIList.begin(), m_cardUIList.end(), m_cardUIList[i]), m_cardUIList.end());
	}
	m_cardUIList.clear();

	ShuffleCard();

	for (int i = cnt - 1; i >= 0; i--)
	{
		int value = rand() % 99 + 1;
		CardRarity rarity;

		if (value <= -1)
			rarity = CardRarity::Legendary;
		else if (value <= -1)
			rarity = CardRarity::Unique;
		else if (value <= -1)
			rarity = CardRarity::Rare;
		else
			rarity = CardRarity::Normal;


		CardUI* ui = GET_SINGLE(SceneManager)->GetCurScene()->Spawn<CardUI>(Layer::UI,
			m_cardStartPos,
			{ 100.f,150.f });
		m_cardUIList.push_back(ui);
		ui->Init(GetCardInfo(m_cardKeyList[rarity][i]));
		ui->MoveToPosition(ui->GetPos(), m_cardPos + m_cardOffset * i);
	}
}

void CardManager::UseCard()
{
	for (size_t i = 0; i < m_cardUIList.size(); i++)
	{
		GET_SINGLE(SceneManager)->GetCurScene()->RequestDestroy(m_cardUIList[i]);
		//m_cardUIList.erase(std::remove(m_cardUIList.begin(), m_cardUIList.end(), m_cardUIList[i]), m_cardUIList.end());
	}
	m_cardUIList.clear();
}

void CardManager::ShuffleCard()
{
	for (int i = 0; i < (int)CardRarity::End; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			int idx1, idx2;
			wstring temp;

			idx1 = rand() % m_cardKeyList[(CardRarity)i].size();
			idx2 = rand() % m_cardKeyList[(CardRarity)i].size();
			temp = m_cardKeyList[(CardRarity)i][idx1];
			m_cardKeyList[(CardRarity)i][idx1] = m_cardKeyList[(CardRarity)i][idx2];
			m_cardKeyList[(CardRarity)i][idx2] = temp;
		}
	}
}
