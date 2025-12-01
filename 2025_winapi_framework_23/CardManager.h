#pragma once
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
private:
	unordered_map<wstring, CardInfo*> m_cardInfoMap;
	vector<CardUI*> m_cardUIList;
	Vector2 m_cardStartPos;
	Vector2 m_cardPos;
	Vector2 m_cardOffset;
	int m_showCardCnt = 5;
};

