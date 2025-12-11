#pragma region include
#include "pch.h"
#include "ResourceManager.h"
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
#include "ShakeCursorCard.h"
#include "SpamCard.h"
#pragma endregion

void CardManager::Init()
{
	m_cardStartPos = { 150, 800 };
	m_cardPos = { 150, 150 };
	m_cardOffset = { 0, 280 };
	//Card* card = GET_SINGLE(SceneManager)->GetCurScene()->Spawn<IndiaInkCard>(Layer::UI, m_cardStartPos, { 100.f,150.f });
	//CardInfo* testCard1 = new CardInfo(L"TestName", L"TestDescription",
	//	L"Bullet", CardRarity::Normal, card);
	////m_cardInfoMap.insert({ testCard1->name, testCard1 });
	//m_cardInfoMap[testCard1->name] = testCard1;
	//m_cardKeyList[CardRarity::Normal].push_back(testCard1->name);

	/*m_cardKeyList[CardRarity::Rare].push_back(L"test");
	m_cardKeyList[CardRarity::Legendary].push_back(L"test");*/

	m_showCardCnt = 2;
}

void CardManager::LateInit()
{
	

}

void CardManager::ShowCard(int cnt,StoneType _curType)
{
	if (cnt <= 0)
		return;

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

		if (value <= 5)
			rarity = CardRarity::Legendary;
		else if (value <= 25)
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

	GET_SINGLE(ResourceManager)->Play(L"ShowCard");
	GET_SINGLE(ResourceManager)->Volume(SOUND_CHANNEL::EFFECT, 1);
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
		if (m_cardKeyList[(CardRarity)i].size() <= 1)
			continue;
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
	RegisterCard<IndiaInkCard>(L"먹물", L"상대턴에\n먹물을 뿌립니다.", L"IndialnkIcon", CardRarity::Rare);
	RegisterCard<EarthquakeCard>(L"지진", L"상대턴에\n지진을 일으킵니다", L"EarthquakeIcon", CardRarity::Rare);
	RegisterCard<PlaceMineCard>(L"지뢰", L"지뢰를 설치하며,\n지뢰가 있는 자리에는 돌을 둘 수 없습니다.", L"PlaceMineIcon", CardRarity::Normal);
	RegisterCard<TimeStopCard>(L"타이무스토뿌", L"사용 즉시\n본인의 시간을 멈춥니다.", L"TimeStopIcon", CardRarity::Normal);
	RegisterCard<DeleteTimeCard>(L"시간 삭제", L"상대의 시간을\n20초 가져 갑니다.", L"DeleteTimeIcon", CardRarity::Rare);
	RegisterCard<ReplaceRandomStoneSkill>(L"매수.", L"상대의 돌을\n랜덤하게 매수합니다.", L"ReplaceRandomStoneIcon", CardRarity::Legendary);
	RegisterCard<RerollCard>(L"리롤", L"카드를 다시\n뽑습니다.", L"RerollIcon", CardRarity::Rare);
	RegisterCard<BlindAllStonesCard>(L"눈가리기", L"상대 턴에\n모든 돌을 숨깁니다.", L"BlindAllStonesIcon", CardRarity::Rare);
	RegisterCard<OneMoreCard>(L"한번 더!", L"한번 더 돌을\n놓을 수 있습니다.", L"OneMoreIcon", CardRarity::Legendary);
	RegisterCard<PeaceCard>(L"평화의 시간", L"이번 턴 후 상대턴과 내 턴 각 한 번 씩 카드가 생성되지 않습니다.", L"PeaceIcon", CardRarity::Normal);

	//11
	RegisterCard<OneMinusCard>(L"카드 뺏기!", L"상대의 카드를\n하나 뺏습니다.", L"OneMinusIcon", CardRarity::Rare);
	RegisterCard<SoundChange>(L"음악 변경!", L"랜덤으로\n음악을 변경합니다.", L"SoundIcon", CardRarity::Normal);
	RegisterCard<StopMusicCard>(L"고독한 시간", L"모든 음악을\n멈춥니다.", L"StopMusicIcon", CardRarity::Normal);
	RegisterCard<ClapCard>(L"매우 축하!", L"박수소리를\n들려줍니다.", L"ClapIcon", CardRarity::Normal);
	RegisterCard<DummyCard>(L"더미 카드!", L"놀랍게도\n아무것도 안 합니다.", L"DummyIcon", CardRarity::Normal);
	RegisterCard<SayHiCard>(L"바른 예의", L"안녕하세요!!!", L"SayHiIcon", CardRarity::Normal);
	RegisterCard<CheeringCard>(L"응원!", L"상대방에게\n응원을 합니다.", L"CheerinIcon", CardRarity::Normal);
	RegisterCard<BlameCard>(L"비난", L"자신에게\n비난을 합니다.", L"BlameIcon", CardRarity::Normal);
	RegisterCard<RestCard>(L"무승부로 하지 않을래...?", L"게임을\n초기화 합니다.", L"RestIcon", CardRarity::Legendary);
	RegisterCard<ShakeCursorCard>(L"수전증", L"상대의 마우스가\n심하게 떱니다.", L"ShakeCursorIcon", CardRarity::Rare);

	//21
	RegisterCard<SpamCard>(L"스팸", L"화면에 스팸을 뿌립니다.", L"SpamIcon", CardRarity::Rare);
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
