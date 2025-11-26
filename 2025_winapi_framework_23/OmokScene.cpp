#include "pch.h"
#include "OmokScene.h"
#include "Board.h"
#include "Card.h"
#include "EarthquakeCard.h"
#include "IndiaInkCard.h"
#include "InputManager.h"
#include "CardManager.h"
#include "SubWindow.h"

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
	SubWindow subWindow = SubWindow(nullptr);
	m_pBoard = new Board;
	m_pBoard->SetPos(Vec2(WINDOW_WIDTH / 2.f, WINDOW_HEIGHT / 2.f));
	m_pBoard->SetSize(Vec2(600.f, 600.f));
	AddObject(m_pBoard, Layer::BOARD);
	//카드
	m_testECard = new EarthquakeCard;
	m_testECard->SetCard(L"지진 카드", L"페시브 형태로 상대턴에 화면을 강하게 흔든다.", CardType::Disturbanc);
	AddObject(m_testECard, Layer::UI);
	m_testICard = new IndiaInkCard;
	m_testICard->SetCard(L"먹물 카드", L"다음 상대턴에 화면을 먹물로 가린다.", CardType::Disturbanc);
	AddObject(m_testICard, Layer::UI);
}

void OmokScene::Update()
{
	Scene::Update();
	if (GET_KEYDOWN(KEY_TYPE::T))
	{
		GET_SINGLE(CardManager)->ShowCard(5);
	}
}

void OmokScene::Render(HDC _hdc)
{
	Scene::Render(_hdc);
}
