#pragma once
#include "Object.h"

class CardInfo;

class CardUI : public Object
{
public:
	CardUI(const CardInfo* cardInfo);
	~CardUI();

private:
	CardInfo* m_cardInfo;
};

