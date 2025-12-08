#pragma once
#include "Card.h"
#include "SceneManager.h"

class CardInfo;
class CardUI;

class CardManager
{
	DECLARE_SINGLE(CardManager);

public:
	void Init();
	void LateInit();

public:
	CardInfo* GetCardInfo(wstring key) { return m_cardInfoMap[key]; }
	void ShowCard(int cnt, StoneType _curType);
	int GetShowCardCnt() { return m_showCardCnt; }
	void UseCard();
	void ShuffleCard();
	void CardDelete();
	void UnRegisterCard();

	template<typename T>
	CardInfo* RegisterCard(wstring _name, wstring _description, wstring _icon, CardRarity _rarity)
	{
		static_assert(std::is_base_of<Card, T>::value, "Card로부터 상속받아야 함");
		
		Card* card = GET_SINGLE(SceneManager)->GetCurScene()->Spawn<T>(Layer::UI, m_cardStartPos, { 100.f,150.f });
		CardInfo* cardInfo = new CardInfo(_name, _description, _icon, _rarity,card);
		m_cardInfoMap[cardInfo->name] = cardInfo;
		m_cardKeyList[_rarity].push_back(cardInfo->name);

		return cardInfo;
	}
private:
	unordered_map<wstring, CardInfo*> m_cardInfoMap;
	//vector<wstring> m_cardKeyList;
	unordered_map<CardRarity, vector<wstring>> m_cardKeyList;
	vector<CardUI*> m_cardUIList;
	Vector2 m_cardStartPos;
	Vector2 m_cardPos;
	Vector2 m_cardOffset;
	int m_showCardCnt = 2;
};

