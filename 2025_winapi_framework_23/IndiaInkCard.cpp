#include "pch.h"
#include "Texture.h"
#include "ResourceManager.h"
#include "IndiaInkCard.h"

IndiaInkCard::IndiaInkCard() :
    m_Tex(nullptr), isInk(false)
	, inkDuration(10.f), inkElapsed(0.f)
	, spawnTimer(0.f), spawnInterval(0.1f)
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
    isSkill = false;
}
void IndiaInkCard::UpdateDoSkill()
{
    spawnTimer += fDT;

    if (spawnTimer >= spawnInterval)
    {
        spawnTimer = 0.f;

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
    }

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
    if (!isSkill) return;
    if (!isInk &&
        curPlayer != GET_SINGLE(BoardManager)->GetCurrentPlayer()) //턴 바뀜
    {
        ReallySkill();
    }

    if (!isInk) return;

    if (isInk &&
        curPlayer == GET_SINGLE(BoardManager)->GetCurrentPlayer()) //턴 바뀜
    {
        NextTurn();
        return;
    }

    UpdateDoSkill();
}

void IndiaInkCard::Render(HDC _hdc)
{
    if (!isSkill) return;
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
            xSize * 4, ySize * 4,
            texDC,
            piece.baseCutX, piece.baseCutY,
            xSize, ySize,
            RGB(0, 0, 0)
        );
    }
}

void IndiaInkCard::CardSkill()
{
    isSkill = true;
    curPlayer = GET_SINGLE(BoardManager)->GetCurrentPlayer();
}