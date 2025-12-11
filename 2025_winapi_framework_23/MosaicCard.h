#pragma once
#include "Card.h"

class MosaicCard
	: public Card
{
public:
	MosaicCard();
	~MosaicCard();
public:
	void Update() override;
	void Render(HDC _hdc) override;
public:
	void CardSkill();
	void NextTurn();
private:
	void ReallySkill();
	HBITMAP Mosaic(HBITMAP src, int w, int h, int block);
private:
	bool isMosaic;
	HBITMAP mosaicBmp = nullptr;
};