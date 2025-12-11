#include "pch.h"
#include "TitleScene.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "Core.h"

TitleScene::TitleScene()
	: m_blinkTimer(0.f)
	, m_showText(true)
{
}

TitleScene::~TitleScene()
{
}

void TitleScene::Init()
{
	GET_SINGLE(ResourceManager)->Stop(SOUND_CHANNEL::BGM);

	GET_SINGLE(ResourceManager)->Play(L"BGM_01");
	GET_SINGLE(ResourceManager)->Volume(SOUND_CHANNEL::BGM, 1.0);
}

void TitleScene::Update()
{
	Scene::Update();

	if (GET_KEYDOWN(KEY_TYPE::ESC))
	{
		PostQuitMessage(0);
	}

	// Space 키를 누르면 오목 씬으로 전환
	if (GET_KEYDOWN(KEY_TYPE::SPACE))
	{
		GET_SINGLE(SceneManager)->LoadScene(L"OmokScene");
	}

	// 텍스트 깜빡임 효과
	m_blinkTimer += fDT;
	if (m_blinkTimer >= 0.5f)
	{
		m_blinkTimer = 0.f;
		m_showText = !m_showText;
	}
}

void TitleScene::Render(HDC _hdc)
{
	Scene::Render(_hdc);

	// 배경색 설정 (검은색)
	HBRUSH bgBrush = CreateSolidBrush(RGB(0, 0, 0));
	HBRUSH oldBrush = (HBRUSH)SelectObject(_hdc, bgBrush);
	Rectangle(_hdc, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	SelectObject(_hdc, oldBrush);
	DeleteObject(bgBrush);

	// 텍스트 설정
	SetBkMode(_hdc, TRANSPARENT);
	SetTextColor(_hdc, RGB(255, 255, 255));

	// 타이틀 텍스트
	HFONT titleFont = CreateFont(
		80, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_SWISS, L"맑은 고딕"
	);
	HFONT oldFont = (HFONT)SelectObject(_hdc, titleFont);

	wstring title = L"Legend of Omok";
	//RECT titleRect = { 0, WINDOW_HEIGHT / 2 - 100, WINDOW_WIDTH, WINDOW_HEIGHT / 2 };
	RECT titleRect = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT -100};
	DrawText(_hdc, title.c_str(), -1, &titleRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	SelectObject(_hdc, oldFont);
	DeleteObject(titleFont);

	// 시작 안내 텍스트 (깜빡임)
	if (m_showText)
	{
		HFONT guideFont = CreateFont(
			40, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
			DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
			ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_SWISS, L"맑은 고딕"
		);
		oldFont = (HFONT)SelectObject(_hdc, guideFont);

		wstring guide = L"Press SPACE to Start";
		//RECT guideRect = { 0, WINDOW_HEIGHT / 2 + 50, WINDOW_WIDTH, WINDOW_HEIGHT / 2 + 100 };
		RECT guideRect = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT +150 };
		DrawText(_hdc, guide.c_str(), -1, &guideRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

		SelectObject(_hdc, oldFont);
		DeleteObject(guideFont);
	}
}
