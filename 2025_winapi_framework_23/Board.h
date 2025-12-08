#pragma once
#include "Object.h"
#include "Stone.h"
#include <utility>

class Texture;
class OmokTimer;
class BoardUI;

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
	bool IsValidMove(int x, int y);
	void Reset();
	void SwitchTurn();
	
#pragma region skill_related

	// 지뢰 관련
	void ActivateMineMode();  // 지뢰 설치 모드 활성화
	bool PlaceMine(int x, int y);  // 지뢰 설치
	bool IsMineMode() const { return m_mineMode; }

	// 돌 교체
	void ReplaceRandomStone();

	void SetBlindAllStones(bool _blind);
#pragma endregion

	
	// 좌표 변환
	bool ScreenToBoard(Vec2 mousePos, int& outX, int& outY) const;
	Vec2 BoardToScreen(int x, int y) const;

	// Getter
	StoneType GetCurrentPlayer() const { return m_currentPlayer; }
	GameState GetGameState() const { return m_gameState; }
	StoneType GetStone(int x, int y) const;
	const std::pair<int, int>& GetLastMove() const { return m_lastMove; }
	OmokTimer* GetTimer() const { return m_timer; }
public :
	bool isPlaced = false;

private:
	bool IsInBounds(int x, int y) const;
	int CountDirection(int x, int y, int dx, int dy, StoneType player) const;
	void RenderBoard(HDC _hdc);
	void RenderHoverPreview(HDC _hdc);
	void RenderMinePreview(HDC _hdc);  // 지뢰 프리뷰 렌더링

private:
	static const int BOARD_SIZE = 19;
	StoneType m_board[BOARD_SIZE][BOARD_SIZE];
	Stone* m_stones[BOARD_SIZE][BOARD_SIZE]; // 바둑돌 객체 배열
	bool m_mines[BOARD_SIZE][BOARD_SIZE]; // 지뢰 위치 배열
	
	// 지뢰 모드 관련
	bool m_mineMode;  // 지뢰 설치 모드 여부
	std::pair<int, int> m_mineHoverPos;  // 지뢰 설치 호버 위치
	bool m_isMineHovering;  // 지뢰 설치 호버 중인지

	// 시간
	OmokTimer* m_timer;
	BoardUI* m_boardUI;

	bool m_blindStones = false; // 바둑돌 블라인드 여부
	
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
};
