#include "pch.h"
#include "Board.h"
#include "GDISelector.h"
#include "InputManager.h"

Board::Board()
	: m_currentPlayer(StoneType::BLACK)
	, m_gameState(GameState::PLAYING)
	, m_cellSize(30.f)
	, m_lastMove(std::make_pair(-1, -1))
	, m_hoverPos(std::make_pair(-1, -1))
	, m_isHovering(false)
	, m_boardColor(RGB(220, 179, 92))
	, m_lineColor(RGB(0, 0, 0))
	, m_blackStoneColor(RGB(30, 30, 30))
	, m_whiteStoneColor(RGB(245, 245, 245))
{
	// 보드 초기화
	for (int y = 0; y < BOARD_SIZE; ++y)
	{
		for (int x = 0; x < BOARD_SIZE; ++x)
		{
			m_board[y][x] = StoneType::NONE;
		}
	}

	m_boardStartPos = Vec2( (WINDOW_WIDTH - (BOARD_SIZE - 1) * m_cellSize) / 2.f,
		(WINDOW_HEIGHT - (BOARD_SIZE - 1) * m_cellSize) / 2.f);
}

Board::~Board()
{
}

void Board::Update()
{
	if (m_gameState != GameState::PLAYING)
		return;

	POINT mousePos = GET_MOUSEPOS;
	Vec2 mousePosVec(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

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
					SwitchTurn();
			}
		}
	}

	if (GET_KEYDOWN(KEY_TYPE::R))
	{
		Reset();
	}
}

void Board::Render(HDC _hdc)
{
	RenderBoard(_hdc);
	RenderStones(_hdc);
	RenderHoverPreview(_hdc);
	RenderUI(_hdc);
}

bool Board::PlaceStone(int x, int y, StoneType player)
{
	if (!IsValidMove(x, y))
		return false;

	m_board[y][x] = player;
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

bool Board::IsValidMove(int x, int y) const
{
	if (!IsInBounds(x, y))
		return false;

	return m_board[y][x] == StoneType::NONE;
}

void Board::Reset()
{
	for (int y = 0; y < BOARD_SIZE; ++y)
	{
		for (int x = 0; x < BOARD_SIZE; ++x)
		{
			m_board[y][x] = StoneType::NONE;
		}
	}

	m_currentPlayer = StoneType::BLACK;
	m_gameState = GameState::PLAYING;
	m_lastMove = std::make_pair(-1, -1);
	m_hoverPos = std::make_pair(-1, -1);
	m_isHovering = false;
}

void Board::SwitchTurn()
{
	if (m_currentPlayer == StoneType::BLACK)
		m_currentPlayer = StoneType::WHITE;
	else
		m_currentPlayer = StoneType::BLACK;
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

void Board::RenderStones(HDC _hdc)
{
	for (int y = 0; y < BOARD_SIZE; ++y)
	{
		for (int x = 0; x < BOARD_SIZE; ++x)
		{
			if (m_board[y][x] == StoneType::NONE)
				continue;

			Vec2 pos = BoardToScreen(x, y);
			float stoneRadius = m_cellSize * 0.45f;

			COLORREF stoneColor = (m_board[y][x] == StoneType::BLACK) ? m_blackStoneColor : m_whiteStoneColor;
			HBRUSH stoneBrush = CreateSolidBrush(stoneColor);
			HPEN stonePen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));

			HBRUSH oldBrush = (HBRUSH)SelectObject(_hdc, stoneBrush);
			HPEN oldPen = (HPEN)SelectObject(_hdc, stonePen);

			Ellipse(_hdc,
				static_cast<int>(pos.x - stoneRadius),
				static_cast<int>(pos.y - stoneRadius),
				static_cast<int>(pos.x + stoneRadius),
				static_cast<int>(pos.y + stoneRadius));

			SelectObject(_hdc, oldBrush);
			SelectObject(_hdc, oldPen);
			DeleteObject(stoneBrush);
			DeleteObject(stonePen);

			// 마지막 수 표시
			if (m_lastMove.first == x && m_lastMove.second == y)
			{
				HPEN redPen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
				oldPen = (HPEN)SelectObject(_hdc, redPen);

				float markRadius = stoneRadius * 0.4f;
				Ellipse(_hdc,
					static_cast<int>(pos.x - markRadius),
					static_cast<int>(pos.y - markRadius),
					static_cast<int>(pos.x + markRadius),
					static_cast<int>(pos.y + markRadius));

				SelectObject(_hdc, oldPen);
				DeleteObject(redPen);
			}
		}
	}
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

	SetBkMode(_hdc, TRANSPARENT);
	SetTextColor(_hdc, RGB(0, 0, 0));

	RECT textRect;
	textRect.left = static_cast<int>(m_boardStartPos.x + (BOARD_SIZE - 1) * m_cellSize + 40.f);
	textRect.top = static_cast<int>(m_boardStartPos.y);
	textRect.right = textRect.left + 200;
	textRect.bottom = textRect.top + 50;

	DrawText(_hdc, turnText.c_str(), -1, &textRect, DT_LEFT | DT_TOP);

	wstring resetText = L"R: 게임 재시작";
	textRect.top += 30;
	textRect.bottom += 30;
	DrawText(_hdc, resetText.c_str(), -1, &textRect, DT_LEFT | DT_TOP);
}

void Board::RenderHoverPreview(HDC _hdc)
{
	if (!m_isHovering || m_gameState != GameState::PLAYING)
		return;

	Vec2 pos = BoardToScreen(m_hoverPos.first, m_hoverPos.second);
	float stoneRadius = m_cellSize * 0.45f;

	COLORREF previewColor = (m_currentPlayer == StoneType::BLACK) ? m_blackStoneColor : m_whiteStoneColor;

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
