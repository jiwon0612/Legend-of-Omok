#pragma once
#include "Object.h"
#include <utility>

class Texture;

enum class StoneType
{
	NONE = 0,
	BLACK = 1,
	WHITE = 2
};

enum class GameState
{
	PLAYING,
	BLACK_WIN,
	WHITE_WIN,
	DRAW
};

class Board : public Object
{
public:
	Board();
	virtual ~Board();

public:
	void Update() override;
	void Render(HDC _hdc) override;

public:
	// 게임 로직
	bool PlaceStone(int x, int y, StoneType player);
	bool CheckWin(int x, int y);
	bool IsValidMove(int x, int y) const;
	void Reset();
	void SwitchTurn();
	
	// 좌표 변환
	bool ScreenToBoard(Vec2 mousePos, int& outX, int& outY) const;
	Vec2 BoardToScreen(int x, int y) const;

	// Getter
	StoneType GetCurrentPlayer() const { return m_currentPlayer; }
	GameState GetGameState() const { return m_gameState; }
	StoneType GetStone(int x, int y) const;
	const std::pair<int, int>& GetLastMove() const { return m_lastMove; }

private:
	bool IsInBounds(int x, int y) const;
	int CountDirection(int x, int y, int dx, int dy, StoneType player) const;
	void RenderBoard(HDC _hdc);
	void RenderStones(HDC _hdc);
	void RenderUI(HDC _hdc);
	void RenderHoverPreview(HDC _hdc);

private:
	static const int BOARD_SIZE = 19;
	StoneType m_board[BOARD_SIZE][BOARD_SIZE];
	
	StoneType m_currentPlayer;
	GameState m_gameState;
	
	Vec2 m_boardStartPos;  // 보드 시작 위치
	float m_cellSize;      // 한 칸의 크기
	
	std::pair<int, int> m_lastMove;  // 마지막 수 위치
	std::pair<int, int> m_hoverPos;  // 마우스 호버 위치
	bool m_isHovering;
	
	// 색상
	COLORREF m_boardColor;
	COLORREF m_lineColor;
	COLORREF m_blackStoneColor;
	COLORREF m_whiteStoneColor;
};
