#include "pch.h"
#include "BoardManager.h"

void BoardManager::Init(Board* board)
{
	m_board = board;
}

void BoardManager::SetPlayerTime(StoneType type, float time)
{
	m_board->playerTime[(int)type - 1] = time;
}

float BoardManager::GetPlayerTime(StoneType type)
{
	return m_board->playerTime[(int)type - 1];
}

void BoardManager::ActivateMineSkill()
{
	if (m_board)
	{
		m_board->ActivateMineMode();
	}
}