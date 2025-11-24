#include "pch.h"
#include "Texture.h"
#include "ResourceManager.h"
#include "IndiaInkCard.h"

IndiaInkCard::IndiaInkCard() : m_Tex(nullptr), isInk(false)
{
	m_Tex = GET_SINGLE(ResourceManager)->GetTexture(L"IndiaInkImage");
    CardSkill();
}
IndiaInkCard::~IndiaInkCard()
{
}
void IndiaInkCard::Update()
{
    if (!isInk) return;

    inkElapsed += fDT;
    inkSpawnElapsed += fDT;

    //생성
    if (inkSpawnElapsed >= inkSpawnInterval)
    {
        inkSpawnElapsed = 0.f;

        LONG texWidth = m_Tex->GetWidth();
        LONG texHeight = m_Tex->GetHeight();

        InkPiece piece;
        int ran = (rand() % 4) + 1;
        piece.baseCutX = xSize * ran;
        ran = (rand() % 3) + 1;
        piece.baseCutY = ySize  * ran;
        piece.screenX = (rand() % 1280) - (ySize * 4);
        piece.screentY = (rand() % 700) - (ySize * 4);
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
        isInk = false;
}

void IndiaInkCard::Render(HDC _hdc)
{
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
    cardName = name;
    this->explanation = explanation;
    cardType = type;
}
void IndiaInkCard::CardSkill()
{
    isInk = true;
    inkDuration = 10.f;
    inkElapsed = 0.f;

    m_inkPieces.clear();
    inkSpawnInterval = 0.3f;
    inkSpawnElapsed = 0.f;
}