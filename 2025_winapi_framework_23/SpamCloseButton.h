#pragma once
#include "Object.h"
class SpamCloseButton
	: public Object
{
public:
	SpamCloseButton(wstring windowType, Vec2 position, Vec2 size);
	~SpamCloseButton() = default;

private:
	// Object을(를) 통해 상속됨
	void Update() override;
	void Render(HDC _hdc) override;

private:
	wstring m_windowType;
	POINT mousePos;
};

