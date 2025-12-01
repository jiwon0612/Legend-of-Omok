#include "pch.h"
#include "OmokScene.h"
#include "Board.h"
#include "Card.h"
#include "EarthquakeCard.h"
#include "IndiaInkCard.h"
#include "InputManager.h"
#include "CardManager.h"
#include "SubWindow.h"
#include "BoardManager.h"

OmokScene::OmokScene()
	: m_pBoard(nullptr)
{
}

OmokScene::~OmokScene()
{
}

void OmokScene::Init()
{
	SubWindow subWindow = SubWindow(nullptr);
}

void OmokScene::LateInit()
{
	// 보드 생성
	m_pBoard = new Board;
	m_pBoard->SetPos(Vec2(WINDOW_WIDTH / 2.f, WINDOW_HEIGHT / 2.f));
	m_pBoard->SetSize(Vec2(600.f, 600.f));
	GET_SINGLE(BoardManager)->Init(m_pBoard);
	AddObject(m_pBoard, Layer::BOARD);
}

void OmokScene::Update()
{
	Scene::Update();
	/*if (GET_KEYDOWN(KEY_TYPE::T))
	{
		GET_SINGLE(CardManager)->ShowCard(5);
	}*/
}

void OmokScene::Render(HDC _hdc)
{
	Scene::Render(_hdc);
}
