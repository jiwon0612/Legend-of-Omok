#pragma once
#include "Scene.h"
#include "EarthquakeCard.h"
#include "IndiaInkCard.h"

class Board;
class ResultWindow;

class OmokScene : public Scene
{
public:
	OmokScene();
	virtual ~OmokScene();

public:
	void Init() override;
	void LateInit() override;
	void Update() override;
	void Render(HDC _hdc) override;

private:
	Board* m_pBoard;
	ResultWindow* m_pResultWindow;
};
