#include "pch.h"
#include "BoardManager.h"
#include "OmokTimer.h"

void BoardManager::Init(Board* board)
{
	m_board = board;
}

void BoardManager::SetPlayerTime(StoneType type, float time)
{
	//m_board->playerTime[(int)type - 1] = time;
	m_board->GetTimer()->SetPlayerTime(type, time);
}

float BoardManager::GetPlayerTime(StoneType type)
{
	//return m_board->playerTime[(int)type - 1];
	return m_board->GetTimer()->GetPlayerTime(type);
}