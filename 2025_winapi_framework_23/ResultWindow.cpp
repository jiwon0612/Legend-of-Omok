#include "pch.h"
#include "ResultWindow.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "CardManager.h"
#include "WindowManager.h"

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
	GET_SINGLE(CardManager)->CardDelete();
	GET_SINGLE(WindowManager)->RemoveAllWindow();
}

void ResultWindow::Show()
{
	GET_SINGLE(CardManager)->UnRegisterCard();

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
	{
		GDISelector brush(_hdc, BrushType::HOLLOW);
		int prevBkMode = SetBkMode(_hdc, TRANSPARENT);
		
		HBRUSH dimBrush = CreateSolidBrush(RGB(0, 0, 0));
		HBRUSH oldBrush = (HBRUSH)SelectObject(_hdc, dimBrush);
		HPEN nullPen = (HPEN)GetStockObject(NULL_PEN);
		HPEN oldPen = (HPEN)SelectObject(_hdc, nullPen);

		for (int i = 0; i < 3; ++i)
		{
			Rectangle(_hdc, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
		}
		
		SelectObject(_hdc, oldPen);
		SelectObject(_hdc, oldBrush);
		DeleteObject(dimBrush);
		SetBkMode(_hdc, prevBkMode);
	}

	// 결과창 박스
	// 화면 크기에 비례하여 박스 크기 설정
	int targetWidth = static_cast<int>(WINDOW_WIDTH ); 
	int targetHeight = static_cast<int>(WINDOW_HEIGHT);

	int boxWidth = static_cast<int>(targetWidth * m_scale) - 150;
	int boxHeight = static_cast<int>(targetHeight * m_scale) - 150;
	int boxX = (WINDOW_WIDTH - boxWidth) / 2;
	int boxY = (WINDOW_HEIGHT - boxHeight) / 2;

	// 그림자
	{
		HBRUSH shadowBrush = CreateSolidBrush(RGB(50, 50, 50));
		HBRUSH oldBrush = (HBRUSH)SelectObject(_hdc, shadowBrush);
		HPEN nullPen = (HPEN)GetStockObject(NULL_PEN);
		HPEN oldPen = (HPEN)SelectObject(_hdc, nullPen);
		
		Rectangle(_hdc, boxX + 10, boxY + 10, boxX + boxWidth + 10, boxY + boxHeight + 10);
		
		SelectObject(_hdc, oldPen);
		SelectObject(_hdc, oldBrush);
		DeleteObject(shadowBrush);
	}

	// 메인 박스
	{
		HBRUSH boxBrush = CreateSolidBrush(RGB(240, 240, 240));
		HPEN boxPen = CreatePen(PS_SOLID, 3, RGB(100, 100, 100));
		HBRUSH oldBrush = (HBRUSH)SelectObject(_hdc, boxBrush);
		HPEN oldPen = (HPEN)SelectObject(_hdc, boxPen);
		
		Rectangle(_hdc, boxX, boxY, boxX + boxWidth, boxY + boxHeight);
		
		SelectObject(_hdc, oldPen);
		SelectObject(_hdc, oldBrush);
		DeleteObject(boxBrush);
		DeleteObject(boxPen);
	}

	if (m_scale >= 0.8f)
	{
		int prevBkMode = SetBkMode(_hdc, TRANSPARENT);

		// 승자 텍스트
		int winnerFontSize = targetHeight / 8; // 폰트 크기 비율 조정
		HFONT winnerFont = CreateFont(
			winnerFontSize, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
			DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
			ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_SWISS, L"-윤고딕330"
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

		COLORREF prevTextColor = SetTextColor(_hdc, winnerColor);
		
		// 텍스트 영역 계산 (상대 좌표)
		RECT winnerRect = { 
			boxX, 
			boxY + static_cast<int>(boxHeight * 0.2f), 
			boxX + boxWidth, 
			boxY + static_cast<int>(boxHeight * 0.5f) 
		};
		DrawText(_hdc, winnerText.c_str(), -1, &winnerRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

		SelectObject(_hdc, oldFont);
		DeleteObject(winnerFont);

		// 안내 텍스트
		int guideFontSize = targetHeight / 20; // 폰트 크기 비율 조정
		HFONT guideFont = CreateFont(
			guideFontSize, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
			DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
			ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_SWISS, L"a자막체"
		);
		oldFont = (HFONT)SelectObject(_hdc, guideFont);

		SetTextColor(_hdc, RGB(80, 80, 80));
		
		wstring guide1 = L"R: 다시 플레이";
		RECT guide1Rect = { 
			boxX, 
			boxY + static_cast<int>(boxHeight * 0.6f), 
			boxX + boxWidth, 
			boxY + static_cast<int>(boxHeight * 0.7f) 
		};
		DrawText(_hdc, guide1.c_str(), -1, &guide1Rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

		wstring guide2 = L"ESC: 타이틀로 돌아가기";
		RECT guide2Rect = { 
			boxX, 
			boxY + static_cast<int>(boxHeight * 0.75f), 
			boxX + boxWidth, 
			boxY + static_cast<int>(boxHeight * 0.85f) 
		};
		DrawText(_hdc, guide2.c_str(), -1, &guide2Rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

		SelectObject(_hdc, oldFont);
		DeleteObject(guideFont);
		SetTextColor(_hdc, prevTextColor);
		SetBkMode(_hdc, prevBkMode);
	}
}
