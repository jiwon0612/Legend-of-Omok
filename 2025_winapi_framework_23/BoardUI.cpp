#include "pch.h"
#include "BoardUI.h"
#include "ResourceManager.h"
#include "Texture.h"

void BoardUI::Update()
{
}

void BoardUI::Render(HDC _hdc)
{
	Texture* stoneTexture = nullptr;
	if (m_gameState == GameState::PLAYING)
	{
		if (m_currentPlayer == StoneType::BLACK)
			stoneTexture = GET_SINGLE(ResourceManager)->GetTexture(L"BlackStone");
		else
			stoneTexture = GET_SINGLE(ResourceManager)->GetTexture(L"WhiteStone");
	}

	SetBkMode(_hdc, TRANSPARENT);
	SetTextColor(_hdc, RGB(0, 0, 0));

	if (stoneTexture)
	{
		// 돌 이미지 그리기
		int stoneX = stoneTexture->GetWidth() / 2 + 190;
		int stoneY = 0;
		TransparentBlt(
			_hdc,
			stoneX, stoneY, stoneTexture->GetWidth(), stoneTexture->GetHeight(),
			stoneTexture->GetTextureDC(),
			0, 0, stoneTexture->GetWidth(), stoneTexture->GetHeight(),
			RGB(255, 0, 255)
		);
	}
}
