#pragma once
#include "Scene.h"
class CardTestScene : public Scene
{
public:
	void Init() override;
	void Update() override;
	void Render(HDC _hdc) override;
};

