#pragma once
#include "Object.h"
class BoardUI :
    public Object
{
public:
    BoardUI() = default;
	virtual ~BoardUI() = default;
	void SetCurrentPlayer(StoneType _type) { m_currentPlayer = _type; }
	void SetGameState(GameState _state) { m_gameState = _state; }

private:
    // Object을(를) 통해 상속됨
    void Update() override;
    void Render(HDC _hdc) override;

private:
    StoneType m_currentPlayer = StoneType::BLACK;
    GameState m_gameState = GameState::PLAYING;
};

