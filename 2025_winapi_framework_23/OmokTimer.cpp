#include "pch.h"
#include "OmokTimer.h"

OmokTimer::OmokTimer()
	: m_elapsedTime(0.f)
	, m_timeStopped(false)
{
	playerTime[0] = TIME_LIMIT; // 흑 시간 초기화
	playerTime[1] = TIME_LIMIT; // 백 시간 초기화
}

OmokTimer::~OmokTimer()
{
}

void OmokTimer::ResetTimer()
{
	m_elapsedTime = 0.f;
	playerTime[0] = TIME_LIMIT; // 흑 시간 초기화
	playerTime[1] = TIME_LIMIT; // 백 시간 초기화
	m_timeStopped = false;
	m_currentPlayer = StoneType::BLACK;
}

void OmokTimer::Update()
{
	if (!m_timeStopped && m_gameState == GameState::PLAYING)
	{
		TimeProcess();
	}
}

void OmokTimer::Render(HDC _hdc)
{
	// 시간 표시
	wstring blackTimeText =
		std::format(L"흑 시간: {:02}:{:02}", static_cast<int>(playerTime[0]) / 60, static_cast<int>(playerTime[0]) % 60);
	wstring whiteTimeText =
		std::format(L"백 시간: {:02}:{:02}", static_cast<int>(playerTime[1]) / 60, static_cast<int>(playerTime[1]) % 60);
	wstring timeText = blackTimeText + L"\n" + whiteTimeText;
	SetBkMode(_hdc, TRANSPARENT);
	SetTextColor(_hdc, RGB(0, 0, 0));
	RECT textRect;
	textRect.left = 20;
	textRect.top = 10;
	textRect.right = textRect.left + 200;
	textRect.bottom = 60;
	DrawText(_hdc, timeText.c_str(), -1, &textRect, DT_LEFT | DT_TOP);
}

void OmokTimer::TimeProcess()
{
	m_elapsedTime += fDT;
	if (m_elapsedTime >= 1.f)
	{
		m_elapsedTime = 0.f;
		if (m_currentPlayer == StoneType::BLACK)
			playerTime[0] -= 1.f;
		else
			playerTime[1] -= 1.f;
		if (playerTime[0] <= 0.f)
			m_gameState = GameState::WHITE_WIN;
		else if (playerTime[1] <= 0.f)
			m_gameState = GameState::BLACK_WIN;
	}
}
