#include "pch.h"
#include "OmokTimer.h"
#include "ResourceManager.h"
#include "Texture.h"

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
    Texture* timerImage = GET_SINGLE(ResourceManager)->GetTexture(L"TimerImage");

    int x = static_cast<int>(GetPos().x);
    int y = static_cast<int>(GetPos().y);
    int w = timerImage->GetWidth();
    int h = timerImage->GetHeight();

    // 타이머 이미지 먼저 그리기
    TransparentBlt(
        _hdc,
        x, y, w, h,
        timerImage->GetTextureDC(),
        0, 0, w, h,
        RGB(255, 0, 255)
    );

    // ---- 시간 문자열 ----
    wstring blackText = std::format(L"{:02}:{:02}",
        static_cast<int>(playerTime[0]) / 60,
        static_cast<int>(playerTime[0]) % 60);

    wstring whiteText = std::format(L"{:02}:{:02}",
        static_cast<int>(playerTime[1]) / 60,
        static_cast<int>(playerTime[1]) % 60);

    SetBkMode(_hdc, TRANSPARENT);
    SetTextColor(_hdc, RGB(0, 0, 0));

    // ---- 중앙 창 영역(대략 테두리 안쪽으로 패딩) ----
    const int paddingX = 32;  // 좌우 여백
    const int paddingY = 36;  // 상하 여백

    int displayLeft = x + paddingX;
    int displayRight = x + w - paddingX;
    int displayTop = y + paddingY;
    int displayBottom = y + h - paddingY;

    // 가운데 세로선 기준으로 반으로 나누기
    int midX = (displayLeft + displayRight) / 2;

    RECT blackRect{ displayLeft, displayTop, midX, displayBottom };
    RECT whiteRect{ midX,      displayTop, displayRight, displayBottom };

    // 각 칸 중앙에 텍스트 배치
    DrawTextW(_hdc, blackText.c_str(), -1, &blackRect,
        DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    DrawTextW(_hdc, whiteText.c_str(), -1, &whiteRect,
        DT_CENTER | DT_VCENTER | DT_SINGLELINE);
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
