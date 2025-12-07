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

OmokScene::OmokScene()
	: m_pBoard(nullptr)
{
}

OmokScene::~OmokScene()
{
}

void OmokScene::Init()
{
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
	/*auto testCard = Spawn<CardUI>(Layer::UI, Vec2(50, 50), Vec2(100.f, 150.f));
	testCard->SetWindowType(L"Sub");*/
}

void OmokScene::Update()
{
	Scene::Update();
	if (GET_KEYDOWN(KEY_TYPE::T))
	{
		//SubWindow subWindow = SubWindow(GET_SINGLE(WindowManager)->GetHInstance());
	}
}

void OmokScene::Render(HDC _hdc)
{
	Scene::Render(_hdc);
}
