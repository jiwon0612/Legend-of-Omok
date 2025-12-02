#pragma once
#include "Object.h"

class ResultWindow : public Object
{
public:
	ResultWindow();
	virtual ~ResultWindow();

public:
	void SetWinner(StoneType winner);
	void Show();
	void Hide();
	bool IsVisible() const { return m_isVisible; }

public:
	void Update() override;
	void Render(HDC _hdc) override;

private:
	bool m_isVisible;
	StoneType m_winner;
	float m_animationTimer;
	float m_scale;
};
