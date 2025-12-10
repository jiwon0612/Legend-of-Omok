#pragma once
#include "Object.h"

class Texture;

class OmokTimer :
	public Object
{
public:
	OmokTimer();
	~OmokTimer();
	void ResetTimer();
	void SetCurrentPlayer(StoneType _type) { m_currentPlayer = _type; }
	void SetGameState(GameState _state) { m_gameState = _state; }
	void SetTimeStopped(bool _stopped) { m_timeStopped = _stopped; }
	void SetPlayerTime(StoneType type, float time) { playerTime[(int)type - 1] = time; }

	//getter
	float GetPlayerTime(StoneType type) { return playerTime[(int)type - 1]; }

private:
	// Object을(를) 통해 상속됨
	void Update() override;
	void Render(HDC _hdc) override;

	void TimeProcess();

private:
	static const int TIME_LIMIT = 180; // 3분
	float m_elapsedTime;
	float playerTime[2]; // 흑, 백 시간

	bool m_timeStopped = false;
	StoneType m_currentPlayer = StoneType::BLACK;
	GameState m_gameState = GameState::PLAYING;

	Texture* timerImage = nullptr;
	Texture* buttonImage = nullptr;
};

