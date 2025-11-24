#include "pch.h"
#include "OmokScene.h"
#include "Board.h"

OmokScene::OmokScene()
	: m_pBoard(nullptr)
{
}

OmokScene::~OmokScene()
{
}

void OmokScene::Init()
{
	// 보드 생성
	m_pBoard = new Board;
	m_pBoard->SetPos(Vec2(WINDOW_WIDTH / 2.f, WINDOW_HEIGHT / 2.f));
	m_pBoard->SetSize(Vec2(600.f, 600.f));
	AddObject(m_pBoard, Layer::BOARD);
}

void OmokScene::Update()
{
	Scene::Update();
}

void OmokScene::Render(HDC _hdc)
{
	Scene::Render(_hdc);
}
