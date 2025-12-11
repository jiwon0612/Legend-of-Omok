#include "pch.h"
#include "MosaicCard.h"
#include "ResourceManager.h"
#include "Core.h"

MosaicCard::MosaicCard() : isMosaic(false) , mosaicBmp(nullptr)
{
}

MosaicCard::~MosaicCard()
{
}
HBITMAP MosaicCard::Mosaic(HBITMAP src, int w, int h, int block)
{
    HDC dc = GetDC(NULL);
    HDC mem1 = CreateCompatibleDC(dc);
    HDC mem2 = CreateCompatibleDC(dc);

    HBITMAP small = CreateCompatibleBitmap(dc, w / block, h / block);
    SelectObject(mem1, small);

    SelectObject(mem2, src);
    StretchBlt(mem1, 0, 0, w / block, h / block,
        mem2, 0, 0, w, h, SRCCOPY);

    HBITMAP big = CreateCompatibleBitmap(dc, w, h);
    SelectObject(mem1, big);
    SelectObject(mem2, small);

    StretchBlt(mem1, 0, 0, w, h,
        mem2, 0, 0, w / block, h / block, SRCCOPY);

    DeleteObject(small);
    DeleteDC(mem1);
    DeleteDC(mem2);
    ReleaseDC(NULL, dc);

    return big; // 모자이크 후 이미지
}

void MosaicCard::ReallySkill()
{
    isMosaic = true;
}

void MosaicCard::NextTurn()
{
    isMosaic = false;
    isSkill = false;
}
void MosaicCard::Update()
{
    if (!isSkill) return;

    if (!isMosaic &&
        curPlayer != GET_SINGLE(BoardManager)->GetCurrentPlayer())
    {
        ReallySkill();

        int w = GetSystemMetrics(SM_CXSCREEN);
        int h = GetSystemMetrics(SM_CYSCREEN);

        HDC hdc = GetDC(NULL);
        HDC mem = CreateCompatibleDC(hdc);

        HBITMAP src = CreateCompatibleBitmap(hdc, w, h);
        SelectObject(mem, src);

        BitBlt(mem, 0, 0, w, h, hdc, 0, 0, SRCCOPY);

        ReleaseDC(NULL, hdc);
        DeleteDC(mem);

        if (mosaicBmp) DeleteObject(mosaicBmp);

        mosaicBmp = Mosaic(src, w, h, 10);

        DeleteObject(src);

    }

    if (!isMosaic) return;

    if (curPlayer == GET_SINGLE(BoardManager)->GetCurrentPlayer())
    {
        NextTurn();
        return;
    }
}
void MosaicCard::Render(HDC _hdc)
{
    if (!isSkill || isMosaic || mosaicBmp == nullptr) return;

    HDC mem = CreateCompatibleDC(_hdc);
    SelectObject(mem, mosaicBmp);

    int screenX = ::GetSystemMetrics(SM_CXSCREEN);
    int screenY = ::GetSystemMetrics(SM_CYSCREEN);
    int winposx = (screenX - WINDOW_WIDTH) / 2 + 100;
    int winposy = (screenY - WINDOW_HEIGHT) / 2 + 200;

    BitBlt(_hdc, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, mem, winposx+20, winposy+40, SRCCOPY);

    DeleteDC(mem);
}


void MosaicCard::CardSkill()
{
    isSkill = true;
    curPlayer = GET_SINGLE(BoardManager)->GetCurrentPlayer();
}
