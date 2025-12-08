#include "pch.h"
#include "ResultWindow.h"
#include "InputManager.h"
#include "SceneManager.h"

ResultWindow::ResultWindow()
	: m_isVisible(false)
	, m_winner(StoneType::NONE)
	, m_animationTimer(0.f)
	, m_scale(0.f)
{
}

ResultWindow::~ResultWindow()
{
}

void ResultWindow::SetWinner(StoneType winner)
{
	m_winner = winner;
}

void ResultWindow::Show()
{
	m_isVisible = true;
	m_animationTimer = 0.f;
	m_scale = 0.f;
}

void ResultWindow::Hide()
{
	m_isVisible = false;
}

void ResultWindow::Update()
{
	if (!m_isVisible)
		return;

	// 팝업 애니메이션
	m_animationTimer += fDT;
	if (m_scale < 1.f)
	{
		m_scale = min(1.f, m_animationTimer * 3.f);
	}

	// R 키로 재시작, ESC 키로 타이틀로 돌아가기
	if (GET_KEYDOWN(KEY_TYPE::R))
	{
		GET_SINGLE(SceneManager)->LoadScene(L"OmokScene");
	}
	else if (GET_KEYDOWN(KEY_TYPE::ESC))
	{
		GET_SINGLE(SceneManager)->LoadScene(L"TitleScene");
	}
}

void ResultWindow::Render(HDC _hdc)
{
	if (!m_isVisible)
		return;

	// 반투명 배경
	HBRUSH dimBrush = CreateSolidBrush(RGB(0, 0, 0));
	HBRUSH oldBrush = (HBRUSH)SelectObject(_hdc, dimBrush);
	HPEN nullPen = (HPEN)GetStockObject(NULL_PEN);
	HPEN oldPen = (HPEN)SelectObject(_hdc, nullPen);

	// 반투명 효과는 SetROP2로 대체
	SetBkMode(_hdc, TRANSPARENT);
	for (int i = 0; i < 3; ++i)
	{
		Rectangle(_hdc, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	}

	SelectObject(_hdc, oldPen);
	SelectObject(_hdc, oldBrush);
	DeleteObject(dimBrush);

	// 결과창 박스
	int boxWidth = static_cast<int>(400 * m_scale);
	int boxHeight = static_cast<int>(300 * m_scale);
	int boxX = WINDOW_WIDTH / 2 - boxWidth / 2;
	int boxY = WINDOW_HEIGHT / 2 - boxHeight / 2;

	// 그림자
	HBRUSH shadowBrush = CreateSolidBrush(RGB(50, 50, 50));
	SelectObject(_hdc, shadowBrush);
	SelectObject(_hdc, nullPen);
	Rectangle(_hdc, boxX + 10, boxY + 10, boxX + boxWidth + 10, boxY + boxHeight + 10);
	DeleteObject(shadowBrush);

	// 메인 박스
	HBRUSH boxBrush = CreateSolidBrush(RGB(240, 240, 240));
	HPEN boxPen = CreatePen(PS_SOLID, 3, RGB(100, 100, 100));
	SelectObject(_hdc, boxBrush);
	SelectObject(_hdc, boxPen);
	Rectangle(_hdc, boxX, boxY, boxX + boxWidth, boxY + boxHeight);

	if (m_scale >= 0.8f)
	{
		// 승자 텍스트
		HFONT winnerFont = CreateFont(
			60, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
			DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
			ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_SWISS, L"맑은 고딕"
		);
		HFONT oldFont = (HFONT)SelectObject(_hdc, winnerFont);

		wstring winnerText;
		COLORREF winnerColor;

		if (m_winner == StoneType::BLACK)
		{
			winnerText = L"흑 승리!";
			winnerColor = RGB(0, 0, 0);
		}
		else if (m_winner == StoneType::WHITE)
		{
			winnerText = L"백 승리!";
			winnerColor = RGB(100, 100, 100);
		}
		else
		{
			winnerText = L"무승부";
			winnerColor = RGB(100, 100, 100);
		}

		SetTextColor(_hdc, winnerColor);
		RECT winnerRect = { boxX, boxY + 50, boxX + boxWidth, boxY + 130 };
		DrawText(_hdc, winnerText.c_str(), -1, &winnerRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

		SelectObject(_hdc, oldFont);
		DeleteObject(winnerFont);

		// 안내 텍스트
		HFONT guideFont = CreateFont(
			25, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
			DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
			ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_SWISS, L"맑은 고딕"
		);
		oldFont = (HFONT)SelectObject(_hdc, guideFont);

		SetTextColor(_hdc, RGB(80, 80, 80));
		
		wstring guide1 = L"R: 다시 플레이";
		RECT guide1Rect = { boxX, boxY + 170, boxX + boxWidth, boxY + 200 };
		DrawText(_hdc, guide1.c_str(), -1, &guide1Rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

		wstring guide2 = L"ESC: 타이틀로 돌아가기";
		RECT guide2Rect = { boxX, boxY + 210, boxX + boxWidth, boxY + 240 };
		DrawText(_hdc, guide2.c_str(), -1, &guide2Rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

		SelectObject(_hdc, oldFont);
		DeleteObject(guideFont);
	}

	DeleteObject(boxBrush);
	DeleteObject(boxPen);
}
