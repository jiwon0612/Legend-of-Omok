#include "pch.h"
#include "OmokScene.h"
#include "Board.h"
#include "Card.h"

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
	//카드
	m_testCard = new Card;
	m_testCard->SetCard(L"먹물 뿌리기", L"상대방의 다음 수를 방해합니다.", CardType::Disturbanc);
	AddObject(m_testCard, Layer::UI);
}

void OmokScene::Update()
{
	Scene::Update();
}

void OmokScene::Render(HDC _hdc)
{
	Scene::Render(_hdc);
}
