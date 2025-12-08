#include "pch.h"
#include "OmokScene.h"
#include "Board.h"
#include "Card.h"
#include "CardUI.h"
#include "EarthquakeCard.h"
#include "IndiaInkCard.h"
#include "InputManager.h"
#include "CardManager.h"
#include "SubWindow.h"
#include "BoardManager.h"
#include "WindowManager.h"
#include "ResultWindow.h"

OmokScene::OmokScene()
	: m_pBoard(nullptr)
	, m_pResultWindow(nullptr)
{
}

OmokScene::~OmokScene()
{
}

void OmokScene::Init()
{
	GET_SINGLE(CardManager)->RegisterCards();
}

void OmokScene::LateInit()
{
	// 보드 생성
	SubWindow subWindow = SubWindow(GET_SINGLE(WindowManager)->GetHInstance(),L"Sub");
	GET_SINGLE(WindowManager)->AddWindow(&subWindow);
	m_pBoard = new Board;
	m_pBoard->SetPos(Vec2(WINDOW_WIDTH / 2.f, WINDOW_HEIGHT / 2.f));
	m_pBoard->SetSize(Vec2(600.f, 600.f));
	GET_SINGLE(BoardManager)->Init(m_pBoard);
	AddObject(m_pBoard, Layer::BOARD);

	// 결과창 생성
	m_pResultWindow = new ResultWindow;
	m_pResultWindow->SetPos(Vec2(WINDOW_WIDTH / 2.f, WINDOW_HEIGHT / 2.f));
	m_pResultWindow->SetSize(Vec2(400.f, 300.f));
	AddObject(m_pResultWindow, Layer::UI);
}

void OmokScene::Update()
{
	Scene::Update();
	
	// 게임이 끝났는지 체크
	if (m_pBoard && m_pResultWindow)
	{
		GameState gameState = m_pBoard->GetGameState();
		if (gameState != GameState::PLAYING && !m_pResultWindow->IsVisible())
		{
			// 게임이 끝났으면 결과창 표시
			if (gameState == GameState::BLACK_WIN)
				m_pResultWindow->SetWinner(StoneType::BLACK);
			else if (gameState == GameState::WHITE_WIN)
				m_pResultWindow->SetWinner(StoneType::WHITE);
			else if (gameState == GameState::DRAW)
				m_pResultWindow->SetWinner(StoneType::NONE);
			
			m_pResultWindow->Show();
		}
	}
}

void OmokScene::Render(HDC _hdc)
{
	Scene::Render(_hdc);
}
