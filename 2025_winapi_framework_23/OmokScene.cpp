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
#include "ResourceManager.h"
#include "WindowAPIs.h"

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
	GET_SINGLE(ResourceManager)->Stop(SOUND_CHANNEL::BGM);

	GET_SINGLE(ResourceManager)->Play(L"BGM_02");
	GET_SINGLE(ResourceManager)->Volume(SOUND_CHANNEL::BGM, 1.0);
}

void OmokScene::LateInit()
{
	//현 바둑판 창 위치
	int screenX = ::GetSystemMetrics(SM_CXSCREEN);
	int screenY = ::GetSystemMetrics(SM_CYSCREEN);
	int winposx = (screenX - WINDOW_WIDTH) / 2 + 100;
	int winposy = (screenY - WINDOW_HEIGHT) / 2 + 100;

	// 보드 생성
	SubWindow* subWindow = new SubWindow(GET_SINGLE(WindowManager)->GetHInstance(),L"Sub",{ winposx - 350 + 15,winposy+100},{350,WINDOW_HEIGHT + 40});
	GET_SINGLE(WindowManager)->AddWindow(subWindow);
	SubWindow* uiWindow = new SubWindow(GET_SINGLE(WindowManager)->GetHInstance(), L"UI", { winposx,winposy-90 }, { WINDOW_WIDTH,200 });
	GET_SINGLE(WindowManager)->AddWindow(uiWindow);
	/*m_pBoard = new Board;
	m_pBoard->SetPos(Vec2(WINDOW_WIDTH / 2.f, WINDOW_HEIGHT / 2.f));
	m_pBoard->SetSize(Vec2(600.f, 600.f));
	GET_SINGLE(BoardManager)->Init(m_pBoard);
	AddObject(m_pBoard, Layer::BOARD);*/

	m_pBoard = Spawn<Board>(Layer::BOARD, Vec2(WINDOW_WIDTH / 2.f, WINDOW_HEIGHT / 2.f), Vec2(600.f, 600.f));
	GET_SINGLE(BoardManager)->Init(m_pBoard);

	// 결과창 생성
	m_pResultWindow = new ResultWindow;
	m_pResultWindow->SetPos(Vec2(WINDOW_WIDTH / 2.f, WINDOW_HEIGHT / 2.f));
	m_pResultWindow->SetSize(Vec2(400.f, 300.f));
	AddObject(m_pResultWindow, Layer::UI);
}

void OmokScene::Update()
{
	Scene::Update();

	if (GET_KEYDOWN(KEY_TYPE::T))
	{
		//::SendMessage(GET_SINGLE(WindowManager)->GetWindowAPIs(L"Sub")->GetHwnd(), WM_CLOSE, 0, 0);
		//GET_SINGLE(WindowManager)->RemoveWindow(GET_SINGLE(WindowManager)->GetSubWindow(L"UI"));
		/*cout << GET_SINGLE(WindowManager)->m_windowAPIs.size() << '\n';
		cout << GET_SINGLE(WindowManager)->m_windows.size() << '\n';*/
	}
	
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
