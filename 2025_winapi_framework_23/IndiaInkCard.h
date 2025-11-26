#pragma once
#include "Card.h"

struct InkPiece
{
	int baseCutX, baseCutY; //자를 위치
	int screenX, screentY;
	int screenSize;
	float alpha;
};

class Texture;
class IndiaInkCard
	: public Card
{
public:
	IndiaInkCard();
	~IndiaInkCard();
public:
	void Update() override;
	void Render(HDC _hdc) override;
public:
	void SetCard(wstring name, wstring explanation, CardType type) override;
	void CardSkill();
private:
	Texture* m_Tex;
	float inkDuration;
	float inkElapsed;
	const int drawCount = 4;
	const int xSize = 153;
	const int ySize = 136;
	const int inkSize = 500;

	std::vector<InkPiece> m_inkPieces;
	float inkSpawnInterval;  // 생성 시간
	float inkSpawnElapsed;   // 누적 시간
};
