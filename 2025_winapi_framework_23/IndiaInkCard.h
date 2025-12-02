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
	void CardSkill();
	void NextTurn();
private:
	void ReallySkill();
	void UpdateDoSkill();
private:
	Texture* m_Tex;

	bool isInk;

	float inkDuration;
	float inkElapsed;
	const int drawCount = 4;
	const int xSize = 153;
	const int ySize = 136;
	const int inkSize = 500;

	float spawnTimer = 0.f;
	float spawnInterval = 0.3f;

	std::vector<InkPiece> m_inkPieces;
};
