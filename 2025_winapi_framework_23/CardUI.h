#pragma once
#include "TweeningObject.h"

class CardInfo;
class Texture;

class CardUI : public TweeningObject
{
public:
	CardUI();
	~CardUI();

public:
	void Init(CardInfo* _cardInfo);
	void Update() override;
	void Render(HDC _hdc) override;

private:
	CardInfo* m_cardInfo;
	Texture* m_cardTex;
	Texture* m_cardIconTex;
	Vector2 m_hoverSizeOffset;
	Vector2 m_defultSize;
	float m_outlineThickness;
	bool m_isInit;
	bool m_isHover;
};

