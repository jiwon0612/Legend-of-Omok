#pragma region include
#include "pch.h"
#include "CardManager.h"
#include "CardInfo.h"
#include "CardUI.h"
#include "EarthquakeCard.h"
#include "IndiaInkCard.h"
#include "PlaceMineCard.h"
#include "TimeStopCard.h"
#include "DeleteTimeCard.h"
#include "ReplaceRandomStoneSkill.h"
#include "RerollCard.h"
#include "BlindAllStonesCard.h"
#include "OneMoreCard.h"
#include "PeaceCard.h"
#include "OneMinusCard.h"
#include "SoundChange.h"
#include "StopMusicCard.h"
#include "ClapCard.h"
#include "DummyCard.h"
#include "SayHiCard.h"
#include "CheeringCard.h"
#include "BlameCard.h"
#include "RestCard.h"
#include "SpamCard.h"
#pragma endregion

void CardManager::Init()
{
	m_cardStartPos = { 500, 500 };
	m_cardPos = { 150, 150 };
	m_cardOffset = { 0, 150 };
	//Card* card = GET_SINGLE(SceneManager)->GetCurScene()->Spawn<IndiaInkCard>(Layer::UI, m_cardStartPos, { 100.f,150.f });
	//CardInfo* testCard1 = new CardInfo(L"TestName", L"TestDescription",
	//	L"Bullet", CardRarity::Normal, card);
	////m_cardInfoMap.insert({ testCard1->name, testCard1 });
	//m_cardInfoMap[testCard1->name] = testCard1;
	//m_cardKeyList[CardRarity::Normal].push_back(testCard1->name);

	m_cardKeyList[CardRarity::Rare].push_back(L"test");
	m_cardKeyList[CardRarity::Unique].push_back(L"test");
	m_cardKeyList[CardRarity::Legendary].push_back(L"test");

	m_showCardCnt = 2;
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
		ui->SetWindowType(L"Sub");
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

void CardManager::CardDelete()
{
	for (size_t i = 0; i < m_cardUIList.size(); i++)
	{
		GET_SINGLE(SceneManager)->GetCurScene()->RequestDestroy(m_cardUIList[i]);
		//m_cardUIList.erase(std::remove(m_cardUIList.begin(), m_cardUIList.end(), m_cardUIList[i]), m_cardUIList.end());
	}
	m_cardUIList.clear();
}

void CardManager::RegisterCards()
{
	RegisterCard<IndiaInkCard>(L"먹물", L"상대의 화면에 먹물을 뿌린다", L"IndialnkIcon", CardRarity::Normal);
	/*RegisterCard<EarthquakeCard>(L"지진", L"상대의 화면에 지진을 이르킨다", L"EarthquakeIcon", CardRarity::Normal);
	RegisterCard<PlaceMineCard>(L"지뢰", L"지뢰를 설치한다 지뢰가 설치된 칸에는 돌을 둘수 없다", L"Bullet", CardRarity::Normal);
	RegisterCard<TimeStopCard>(L"타이무스토뿌", L"시간을 멈춘다", L"Bullet", CardRarity::Normal);
	RegisterCard<DeleteTimeCard>(L"시간 삭제", L"시간을 삭제한다", L"Bullet", CardRarity::Normal);
	RegisterCard<ReplaceRandomStoneSkill>(L"돌 교체", L"돌을 교체한다", L"Bullet", CardRarity::Normal);
	RegisterCard<RerollCard>(L"리롤", L"카드를 다시 뽑는다", L"Bullet", CardRarity::Normal);
	RegisterCard<BlindAllStonesCard>(L"눈가리기", L"모든 돌을 블라인드 상태로 만든다", L"Bullet", CardRarity::Normal);
	RegisterCard<OneMoreCard>(L"한번 더!", L"한번 더 돌을 놓을 수 있다", L"Bullet", CardRarity::Normal);
	RegisterCard<PeaceCard>(L"평화의 시간", L"이번 턴 후 상대 턴과 내 턴 각 한 번 씩 카드가 생성되지 않는다.", L"Bullet", CardRarity::Normal);
	RegisterCard<OneMinusCard>(L"카드 뺏기!", L"상대의 카드를 하나 뺏는다", L"Bullet", CardRarity::Normal);
	RegisterCard<SoundChange>(L"음악 변경!", L"랜덤으로 음악을 변경한다.", L"Bullet", CardRarity::Normal);
	RegisterCard<StopMusicCard>(L"고독한 시간", L"모든 음악을 멈춘다.", L"Bullet", CardRarity::Normal);
	RegisterCard<ClapCard>(L"매우 축하!", L"박수소리를!", L"Bullet", CardRarity::Normal);
	RegisterCard<DummyCard>(L"더미 카드!", L"놀랍게도 아무것도 안 합니다!", L"Bullet", CardRarity::Normal);
	RegisterCard<SayHiCard>(L"바른 예의", L"안녕하세요!!!", L"Bullet", CardRarity::Normal);
	RegisterCard<CheeringCard>(L"응원!", L"상대방에게 응원을 합니다.", L"Bullet", CardRarity::Normal);
	RegisterCard<BlameCard>(L"비난", L"자신에게 비난을 합니다.", L"Bullet", CardRarity::Normal);
	RegisterCard<RestCard>(L"휴식", L"게임을 초기화 합니다.", L"Bullet", CardRarity::Normal);*/
	RegisterCard<SpamCard>(L"스팸", L"화면에 스팸을 뿌립니다.", L"Bullet", CardRarity::Normal);
}

void CardManager::UnRegisterCard()
{
	//CardDelete();
	for (auto& pair : m_cardInfoMap)
	{
		SAFE_DELETE(pair.second);
	}
	m_cardInfoMap.clear();
	m_cardKeyList.clear();
}
