#include "pch.h"
#include "BoardUI.h"

void BoardUI::Update()
{
}

void BoardUI::Render(HDC _hdc)
{
	wstring turnText;
	if (m_gameState == GameState::PLAYING)
	{
		if (m_currentPlayer == StoneType::BLACK)
			turnText = L"현재 턴: 흑";
		else
			turnText = L"현재 턴: 백";
	}
	else if (m_gameState == GameState::BLACK_WIN)
		turnText = L"흑 승리!";
	else if (m_gameState == GameState::WHITE_WIN)
		turnText = L"백 승리!";

	SetBkMode(_hdc, TRANSPARENT);
	SetTextColor(_hdc, RGB(0, 0, 0));

	RECT textRect;
	textRect.left = 20;
	textRect.top = 45;
	textRect.right = textRect.left + 200;
	textRect.bottom = textRect.top + 50;

	DrawText(_hdc, turnText.c_str(), -1, &textRect, DT_LEFT | DT_TOP);
	textRect.top += 50;
	textRect.bottom += 50;

	wstring resetText = L"R: 게임 재시작";
	textRect.top += 30;
	DrawText(_hdc, resetText.c_str(), -1, &textRect, DT_LEFT | DT_TOP);
}
