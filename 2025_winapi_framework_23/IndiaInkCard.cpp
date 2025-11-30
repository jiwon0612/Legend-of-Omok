#include "pch.h"
#include "Texture.h"
#include "ResourceManager.h"
#include "IndiaInkCard.h"

IndiaInkCard::IndiaInkCard() : 
    m_Tex(nullptr), isInk(false)
{
	m_Tex = GET_SINGLE(ResourceManager)->GetTexture(L"IndiaInkImage");
}
IndiaInkCard::~IndiaInkCard()
{
}

void IndiaInkCard::ReallySkill()
{
    isInk = true;

    inkDuration = 10.f;
    inkElapsed = 0.f;

    m_inkPieces.clear();
}
void IndiaInkCard::NextTurn()
{
    isInk = false;
    Card::NextTurn();
}
void IndiaInkCard::UpdateDoSkill()
{
    inkElapsed += fDT;

    //생성
    LONG texWidth = m_Tex->GetWidth();
    LONG texHeight = m_Tex->GetHeight();

    InkPiece piece;
    int ran = (rand() % 4) + 1;
    piece.baseCutX = xSize * ran;
    ran = (rand() % 3) + 1;
    piece.baseCutY = ySize * ran;
    piece.screenX = (rand() % WINDOW_WIDTH) - (ySize * 4);
    piece.screentY = (rand() % WINDOW_WIDTH) - (ySize * 4);
    piece.screenSize = inkSize;
    piece.alpha = 200.f;

    m_inkPieces.push_back(piece);

    //투명도
    for (auto& piece : m_inkPieces)
    {
        piece.alpha -= 200.f * fDT / inkDuration;
        if (piece.alpha < 0.f) piece.alpha = 0.f;
    }

    // 제거
    m_inkPieces.erase(
        std::remove_if(m_inkPieces.begin(), m_inkPieces.end(),
            [](const InkPiece& p) { return p.alpha <= 0.f; }),
        m_inkPieces.end()
    );

    if (inkElapsed >= inkDuration && m_inkPieces.empty())
        isSkill = false;
}

void IndiaInkCard::Update()
{
    Card::Update();

    if (!isInk && 
        curPlayer != GET_SINGLE(BoardManager)->GetCurrentPlayer()) //턴 바뀜
    {
        ReallySkill();
    }

    if (!isInk) return;

    if (!isInk &&
        curPlayer == GET_SINGLE(BoardManager)->GetCurrentPlayer()) //턴 바뀜
    {
        NextTurn();
    }

    UpdateDoSkill();
}

void IndiaInkCard::Render(HDC _hdc)
{
    Card::Render(_hdc);
    if (!isInk) return;

    HDC texDC = m_Tex->GetTextureDC();

    BLENDFUNCTION bf = {};
    bf.BlendOp = AC_SRC_OVER;
    bf.SourceConstantAlpha = 200;
    bf.AlphaFormat = 0;

    for (const auto& piece : m_inkPieces)
    {
        bf.SourceConstantAlpha = static_cast<BYTE>(piece.alpha);

        ::TransparentBlt(
            _hdc,
            piece.screenX, piece.screentY,
            xSize *4, ySize*4,
            texDC,
            piece.baseCutX, piece.baseCutY,
            xSize, ySize,
            RGB(0, 0, 0)
        );
    }
}


void IndiaInkCard::SetCard(wstring name, wstring explanation, CardType type)
{
   Card::SetCard(name, explanation, type);
}
void IndiaInkCard::CardSkill()
{
    Card::CardSkill();
}