#pragma once
#include"Board.h"

class BoardManager
{
	DECLARE_SINGLE(BoardManager);
public:
	void Init(Board* board);
public:
	//void SetCurrentPlayer(StoneType stone) { m_board->m_currentPlayer = stone; }
	StoneType GetCurrentPlayer() const { return  m_board->GetCurrentPlayer(); }
	void SetPlayerTime(StoneType type, float time);
	float GetPlayerTime(StoneType type);
	
	// 지뢰 스킬
	void ActivateMineSkill();
private:
	Board* m_board = nullptr;
private:
};