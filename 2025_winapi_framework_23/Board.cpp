#include "pch.h"
#include "Board.h"
#include "GDISelector.h"
#include "InputManager.h"
#include "CardManager.h"
#include "SceneManager.h"

Board::Board()
	: m_currentPlayer(StoneType::BLACK)
	, m_gameState(GameState::PLAYING)
	, m_cellSize(30.f)
	, m_lastMove(std::make_pair(-1, -1))
	, m_hoverPos(std::make_pair(-1, -1))
	, m_isHovering(false)
	, m_boardColor(RGB(220, 179, 92))
	, m_lineColor(RGB(0, 0, 0))
	, playerTime{ TIME_LIMIT, TIME_LIMIT }
	, m_elapsedTime(0.f)
	, m_mines{ false }
	, m_stones{ nullptr }
	, m_board{ StoneType::NONE }
	, m_mineMode(false)
	, m_mineHoverPos(std::make_pair(-1, -1))
	, m_isMineHovering(false)
{
	m_boardStartPos = Vec2( (WINDOW_WIDTH - (BOARD_SIZE - 1) * m_cellSize) / 2.f,
		(WINDOW_HEIGHT - (BOARD_SIZE - 1) * m_cellSize) / 2.f);

	GET_SINGLE(CardManager)->ShowCard(5, StoneType::BLACK);
}

Board::~Board()
{
}

void Board::Update()
{
	if (m_gameState != GameState::PLAYING)
		return;

	// 시간 처리
	if (!m_timeStopped)
		TimeProcess();

	if (GET_KEYDOWN(KEY_TYPE::R))
		Reset();

	POINT mousePos = GET_MOUSEPOS;
	Vec2 mousePosVec(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

	// 지뢰 모드 처리
	if (m_mineMode)
	{
		// 지뢰 설치 호버 처리
		int hoverX, hoverY;
		if (ScreenToBoard(mousePosVec, hoverX, hoverY))
		{
			// 이미 돌이 있는 곳에는 설치 불가
			if (m_board[hoverY][hoverX] == StoneType::NONE)
			{
				m_mineHoverPos = std::make_pair(hoverX, hoverY);
				m_isMineHovering = true;
			}
			else
			{
				m_isMineHovering = false;
			}
		}
		else
		{
			m_isMineHovering = false;
		}

		// 지뢰 설치 클릭 처리
		if (GET_KEYDOWN(KEY_TYPE::LBUTTON))
		{
			int boardX, boardY;
			if (ScreenToBoard(mousePosVec, boardX, boardY))
			{
				if (PlaceMine(boardX, boardY))
				{
					// 지뢰 설치 성공
					m_mineMode = false;
					m_isMineHovering = false;
					// isPlaced는 그대로 유지 (착수했으면 true, 안 했으면 false)
				}
			}
		}
		return; // 지뢰 모드에서는 일반 착수 처리 안 함
	}

	if (isPlaced) return;

	// 마우스 호버 처리
	int hoverX, hoverY;
	if (ScreenToBoard(mousePosVec, hoverX, hoverY))
	{
		if (IsValidMove(hoverX, hoverY))
		{
			m_hoverPos = std::make_pair(hoverX, hoverY);
			m_isHovering = true;
		}
		else
		{
			m_isHovering = false;
		}
	}
	else
	{
		m_isHovering = false;
	}

	// 마우스 클릭 처리
	if (GET_KEYDOWN(KEY_TYPE::LBUTTON))
	{
		int boardX, boardY;
		if (ScreenToBoard(mousePosVec, boardX, boardY))
		{
			if (PlaceStone(boardX, boardY, m_currentPlayer))
			{
				if (CheckWin(boardX, boardY))
				{
					if (m_currentPlayer == StoneType::BLACK)
						m_gameState = GameState::BLACK_WIN;
					else
						m_gameState = GameState::WHITE_WIN;
				}
				else
				{ 
					isPlaced = true;
					SwitchTurn();
				}
			}
		}
	}
}

void Board::TimeProcess()
{
	m_elapsedTime += fDT;
	if (m_elapsedTime >= 1.f)
	{
		m_elapsedTime = 0.f;
		if (m_currentPlayer == StoneType::BLACK)
			playerTime[0] -= 1.f;
		else
			playerTime[1] -= 1.f;
		if (playerTime[0] <= 0.f)
			m_gameState = GameState::WHITE_WIN;
		else if (playerTime[1] <= 0.f)
			m_gameState = GameState::BLACK_WIN;
	}
}

void Board::Render(HDC _hdc)
{
	RenderBoard(_hdc);
	RenderHoverPreview(_hdc);
	RenderMinePreview(_hdc);
	RenderUI(_hdc);
}

bool Board::PlaceStone(int x, int y, StoneType player)
{
	if (!IsValidMove(x, y))
		return false;

	// 지뢰가 있는 곳인지 확인
	if (m_mines[y][x])
	{
		// 지뢰 터짐! 착수 무효화
		m_mines[y][x] = false;  // 지뢰 제거
		SwitchTurn();  // 턴 넘기기
		return false;  // 착수 실패
	}

	m_board[y][x] = player;

	Vec2 stonePos = BoardToScreen(x, y);
	Stone* newStone = new Stone(player, Vec2(m_cellSize - 4.f, m_cellSize - 4.f), stonePos);
	m_stones[y][x] = newStone;
	
	GET_SINGLE(SceneManager)->GetCurScene()->AddObject(newStone, Layer::STONE);

	m_lastMove = std::make_pair(x, y);
	return true;
}

bool Board::CheckWin(int x, int y)
{
	StoneType player = m_board[y][x];
	if (player == StoneType::NONE)
		return false;

	int directions[4][2] = { {1, 0}, {0, 1}, {1, 1}, {1, -1} };

	for (int d = 0; d < 4; ++d)
	{
		int dx = directions[d][0];
		int dy = directions[d][1];

		int count = 1;
		count += CountDirection(x, y, dx, dy, player);   // 정방향
		count += CountDirection(x, y, -dx, -dy, player); // 역방향

		if (count == 5) // 정확히 5개 (6개 안됨)
			return true;
	}

	return false;
}

bool Board::IsValidMove(int x, int y)
{
	if (!IsInBounds(x, y))
		return false;

	if (m_board[y][x] != StoneType::NONE && m_blindStones)
	{
		SwitchTurn();
		return false;
	}

	return m_board[y][x] == StoneType::NONE;
}

void Board::Reset()
{
	for (int y = 0; y < BOARD_SIZE; ++y)
	{
		for (int x = 0; x < BOARD_SIZE; ++x)
		{
			m_board[y][x] = StoneType::NONE;
			m_mines[y][x] = false;  // 지뢰도 초기화
		}
	}
	for (int y = 0; y < BOARD_SIZE; ++y)
	{
		for (int x = 0; x < BOARD_SIZE; ++x)
		{
			if (m_stones[y][x])
			{
				m_stones[y][x]->SetDead();
				m_stones[y][x] = nullptr;
			}
		}
	}

	m_currentPlayer = StoneType::BLACK;
	m_gameState = GameState::PLAYING;
	m_lastMove = std::make_pair(-1, -1);
	m_hoverPos = std::make_pair(-1, -1);
	m_isHovering = false;
	isPlaced = false;
	playerTime[0] = TIME_LIMIT;
	playerTime[1] = TIME_LIMIT;
	
	// 지뢰 모드 초기화
	m_mineMode = false;
	m_mineHoverPos = std::make_pair(-1, -1);
	m_isMineHovering = false;
}

void Board::SwitchTurn()
{
	isPlaced = false;
	m_timeStopped = false;

	if (m_blindStones)
	{
		m_blindStones = false;
		SetBlindAllStones(false);
	}

	if (m_currentPlayer == StoneType::BLACK)
		m_currentPlayer = StoneType::WHITE;
	else
		m_currentPlayer = StoneType::BLACK;
	GET_SINGLE(CardManager)->ShowCard(GET_SINGLE(CardManager)->GetShowCardCnt(),m_currentPlayer);
}

void Board::TimeStop()
{
	m_timeStopped = true;
}

void Board::ReplaceRandomStone()
{
	// 랜덤한 상대돌을 내 돌로 교체
	vector<std::pair<int, int>> opponentStones;
	StoneType opponent = (m_currentPlayer == StoneType::BLACK) ? StoneType::WHITE : StoneType::BLACK;
	for (int y = 0; y < BOARD_SIZE; ++y)
	{
		for (int x = 0; x < BOARD_SIZE; ++x)
		{
			if (m_board[y][x] == opponent)
			{
				opponentStones.push_back(std::make_pair(x, y));
			}
		}
	}
	if (opponentStones.empty())
		return;
	int randIndex = rand() % opponentStones.size();
	int rx = opponentStones[randIndex].first;
	int ry = opponentStones[randIndex].second;
	// 돌 교체
	m_board[ry][rx] = m_currentPlayer;
	Stone* oldStone = m_stones[ry][rx];
	if (oldStone)
	{
		oldStone->SetDead();
	}
	Vec2 stonePos = BoardToScreen(rx, ry);
	Stone* newStone = new Stone(m_currentPlayer, Vec2(m_cellSize - 4.f, m_cellSize - 4.f), stonePos);
	m_stones[ry][rx] = newStone;
	GET_SINGLE(SceneManager)->GetCurScene()->AddObject(newStone, Layer::STONE);
}

void Board::SetBlindAllStones(bool _blind)
{
	m_blindStones = _blind;
	for (int y = 0; y < BOARD_SIZE; ++y)
	{
		for (int x = 0; x < BOARD_SIZE; ++x)
		{
			if (m_stones[y][x])
			{
				m_stones[y][x]->SetBlind(_blind);
			}
		}
	}
}

bool Board::ScreenToBoard(Vec2 mousePos, int& outX, int& outY) const
{
	// 마우스 위치에서 보드 시작 위치를 뺀 후, 셀 크기로 나눔
	float relX = mousePos.x - m_boardStartPos.x;
	float relY = mousePos.y - m_boardStartPos.y;

	// 교점 기준으로 계산 (가장 가까운 교점)
	int boardX = static_cast<int>(round(relX / m_cellSize));
	int boardY = static_cast<int>(round(relY / m_cellSize));

	float distX = abs(relX - boardX * m_cellSize);
	float distY = abs(relY - boardY * m_cellSize);
	float threshold = m_cellSize * 0.3f;

	if (distX > threshold || distY > threshold)
		return false;

	if (!IsInBounds(boardX, boardY))
		return false;

	outX = boardX;
	outY = boardY;
	return true;
}

Vec2 Board::BoardToScreen(int x, int y) const
{
	float screenX = m_boardStartPos.x + x * m_cellSize;
	float screenY = m_boardStartPos.y + y * m_cellSize;
	return Vec2(screenX, screenY);
}

StoneType Board::GetStone(int x, int y) const
{
	if (!IsInBounds(x, y))
		return StoneType::NONE;
	return m_board[y][x];
}

bool Board::IsInBounds(int x, int y) const
{
	return x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE;
}

int Board::CountDirection(int x, int y, int dx, int dy, StoneType player) const
{
	int count = 0;
	int nx = x + dx;
	int ny = y + dy;

	while (IsInBounds(nx, ny) && m_board[ny][nx] == player)
	{
		count++;
		nx += dx;
		ny += dy;
	}

	return count;
}

void Board::RenderBoard(HDC _hdc)
{
	// 바둑판 배경
	HBRUSH boardBrush = CreateSolidBrush(m_boardColor);
	HBRUSH oldBrush = (HBRUSH)SelectObject(_hdc, boardBrush);

	float boardWidth = (BOARD_SIZE - 1) * m_cellSize + 40.f;
	float boardHeight = (BOARD_SIZE - 1) * m_cellSize + 40.f;

	Rectangle(_hdc,
		static_cast<int>(m_boardStartPos.x - 20.f),
		static_cast<int>(m_boardStartPos.y - 20.f),
		static_cast<int>(m_boardStartPos.x + boardWidth - 20.f),
		static_cast<int>(m_boardStartPos.y + boardHeight - 20.f));

	SelectObject(_hdc, oldBrush);
	DeleteObject(boardBrush);

	// 바둑판 선
	HPEN linePen = CreatePen(PS_SOLID, 1, m_lineColor);
	HPEN oldPen = (HPEN)SelectObject(_hdc, linePen);

	for (int i = 0; i < BOARD_SIZE; ++i)
	{
		Vec2 start = BoardToScreen(0, i);
		Vec2 end = BoardToScreen(BOARD_SIZE - 1, i);

		MoveToEx(_hdc, static_cast<int>(start.x), static_cast<int>(start.y), nullptr);
		LineTo(_hdc, static_cast<int>(end.x), static_cast<int>(end.y));
	}

	for (int i = 0; i < BOARD_SIZE; ++i)
	{
		Vec2 start = BoardToScreen(i, 0);
		Vec2 end = BoardToScreen(i, BOARD_SIZE - 1);

		MoveToEx(_hdc, static_cast<int>(start.x), static_cast<int>(start.y), nullptr);
		LineTo(_hdc, static_cast<int>(end.x), static_cast<int>(end.y));
	}

	// 화점 그리기
	int starPoints[9][2] = {
		{3, 3}, {3, 9}, {3, 15},
		{9, 3}, {9, 9}, {9, 15},
		{15, 3}, {15, 9}, {15, 15}
	};

	HBRUSH starBrush = CreateSolidBrush(m_lineColor);
	SelectObject(_hdc, starBrush);

	for (int i = 0; i < 9; ++i)
	{
		Vec2 pos = BoardToScreen(starPoints[i][0], starPoints[i][1]);
		Ellipse(_hdc,
			static_cast<int>(pos.x - 3),
			static_cast<int>(pos.y - 3),
			static_cast<int>(pos.x + 3),
			static_cast<int>(pos.y + 3));
	}

	SelectObject(_hdc, oldPen);
	DeleteObject(linePen);
	DeleteObject(starBrush);
}

void Board::RenderUI(HDC _hdc)
{
	wstring turnText;
	if (m_gameState == GameState::PLAYING)
	{
		if (m_currentPlayer == StoneType::BLACK)
			turnText = L"현재 턴: 흑";
		else
			turnText = L"현재 턴: 백";
	}
	else if (m_gameState == GameState::BLACK_WIN)
		turnText = L"흑 승리!";
	else if (m_gameState == GameState::WHITE_WIN)
		turnText = L"백 승리!";

	// 시간 표시
	wstring blackTimeText = 
		std::format(L"흑 시간: {:02}:{:02}", static_cast<int>(playerTime[0]) / 60, static_cast<int>(playerTime[0]) % 60);
	wstring whiteTimeText = 
		std::format(L"백 시간: {:02}:{:02}", static_cast<int>(playerTime[1]) / 60, static_cast<int>(playerTime[1]) % 60);
	wstring timeText = blackTimeText + L"\n" + whiteTimeText;

	SetBkMode(_hdc, TRANSPARENT);
	SetTextColor(_hdc, RGB(0, 0, 0));

	RECT textRect;
	textRect.left = static_cast<int>(m_boardStartPos.x + (BOARD_SIZE - 1) * m_cellSize + 40.f);
	textRect.top = static_cast<int>(m_boardStartPos.y);
	textRect.right = textRect.left + 200;
	textRect.bottom = textRect.top + 50;

	DrawText(_hdc, turnText.c_str(), -1, &textRect, DT_LEFT | DT_TOP);
	textRect.top += 50;
	textRect.bottom += 50;
	DrawText(_hdc, timeText.c_str(), -1, &textRect, DT_LEFT | DT_TOP);

	wstring resetText = L"R: 게임 재시작";
	textRect.top += 70;
	textRect.bottom += 70;
	DrawText(_hdc, resetText.c_str(), -1, &textRect, DT_LEFT | DT_TOP);
}

void Board::RenderHoverPreview(HDC _hdc)
{
	if (!m_isHovering || m_gameState != GameState::PLAYING || m_mineMode)
		return;

	Vec2 pos = BoardToScreen(m_hoverPos.first, m_hoverPos.second);
	float stoneRadius = m_cellSize * 0.45f;

	COLORREF previewColor = (m_currentPlayer == StoneType::BLACK) ? RGB(50, 50, 50) : RGB(200, 200, 200);

	HPEN previewPen = CreatePen(PS_DOT, 2, previewColor);
	HBRUSH hollowBrush = (HBRUSH)GetStockObject(NULL_BRUSH);

	HPEN oldPen = (HPEN)SelectObject(_hdc, previewPen);
	HBRUSH oldBrush = (HBRUSH)SelectObject(_hdc, hollowBrush);

	Ellipse(_hdc,
		static_cast<int>(pos.x - stoneRadius),
		static_cast<int>(pos.y - stoneRadius),
		static_cast<int>(pos.x + stoneRadius),
		static_cast<int>(pos.y + stoneRadius));

	SelectObject(_hdc, oldPen);
	SelectObject(_hdc, oldBrush);
	DeleteObject(previewPen);
}

void Board::RenderMinePreview(HDC _hdc)
{
	if (!m_isMineHovering || m_gameState != GameState::PLAYING || !m_mineMode)
		return;

	Vec2 pos = BoardToScreen(m_mineHoverPos.first, m_mineHoverPos.second);
	float mineSize = m_cellSize * 0.4f;

	// 빨간색 X 표시로 지뢰 프리뷰
	HPEN minePen = CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
	HPEN oldPen = (HPEN)SelectObject(_hdc, minePen);

	// X 표시 그리기
	MoveToEx(_hdc, static_cast<int>(pos.x - mineSize), static_cast<int>(pos.y - mineSize), nullptr);
	LineTo(_hdc, static_cast<int>(pos.x + mineSize), static_cast<int>(pos.y + mineSize));
	
	MoveToEx(_hdc, static_cast<int>(pos.x + mineSize), static_cast<int>(pos.y - mineSize), nullptr);
	LineTo(_hdc, static_cast<int>(pos.x - mineSize), static_cast<int>(pos.y + mineSize));

	SelectObject(_hdc, oldPen);
	DeleteObject(minePen);
}

void Board::ActivateMineMode()
{
	m_mineMode = true;
	m_isMineHovering = false;
}

bool Board::PlaceMine(int x, int y)
{
	if (!IsInBounds(x, y))
		return false;

	// 이미 돌이 있는 곳에는 설치 불가
	if (m_board[y][x] != StoneType::NONE)
		return false;

	// 이미 지뢰가 있는 곳에도 설치 불가
	if (m_mines[y][x])
		return false;

	m_mines[y][x] = true;
	return true;
}
