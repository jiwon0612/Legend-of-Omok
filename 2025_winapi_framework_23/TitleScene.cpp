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
	GDISelector bgBrush = GDISelector(_hdc, BrushType::BLACK);
	Rectangle(_hdc, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

	// 텍스트 설정
	SetBkMode(_hdc, TRANSPARENT);
	SetTextColor(_hdc, RGB(255, 255, 255));

	// 타이틀 텍스트
	GDISelector titleFont =  GDISelector(_hdc, FontType::TITLE);

	wstring title = L"Legend of Omok";
	RECT titleRect = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT -100};
	DrawText(_hdc, title.c_str(), -1, &titleRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	// 시작 안내 텍스트 (깜빡임)
	if (m_showText)
	{
		GDISelector guidFont = GDISelector(_hdc, FontType::GUIDE);

		wstring guide = L"Press SPACE to Start";
		RECT guideRect = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT +150 };
		DrawText(_hdc, guide.c_str(), -1, &guideRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}

	// 우하단에 나가기 안내 텍스트
	GDISelector exitFont = GDISelector(_hdc, FontType::UI);
	wstring exitGuide = L"Press ESC to Exit";
	RECT exitRect = { WINDOW_WIDTH - 300, WINDOW_HEIGHT - 50, WINDOW_WIDTH - 10, WINDOW_HEIGHT - 10 };
	DrawText(_hdc, exitGuide.c_str(), -1, &exitRect, DT_RIGHT | DT_VCENTER | DT_SINGLELINE);

	// 좌하단에 제작자 텍스트
	GDISelector creatorFont = GDISelector(_hdc, FontType::UI);
	wstring creatorText = L"Created by 정예은, 최지원, 최찬호";
	RECT creatorRect = { 10, WINDOW_HEIGHT - 50, 300, WINDOW_HEIGHT - 10 };
	DrawText(_hdc, creatorText.c_str(), -1, &creatorRect, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
}
