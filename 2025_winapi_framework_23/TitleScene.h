#pragma once
#include "Scene.h"

class TitleScene : public Scene
{
public:
	TitleScene();
	virtual ~TitleScene();

public:
	void Init() override;
	void Update() override;
	void Render(HDC _hdc) override;

private:
	float m_blinkTimer;
	bool m_showText;
};
