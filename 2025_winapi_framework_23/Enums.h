#pragma once
enum class Layer
{
	DEFAULT,
	BACKGROUND,
	BOARD,
	STONE,
	PLAYER,
	ENEMY,
	PROJECTILE,
	UI,
	BUTTON,
	TEXT,
	END
};
enum class PenType
{
	RED, GREEN, END
};
enum class BrushType
{
	HOLLOW, RED, GREEN, END
};

enum class FontType
{
	UI, TITLE, END
};

enum class PlayMode
{
	Once, Loop, Counted
};

enum class CardRarity
{
	Normal = 0, Rare, Unique, Legendary
	, End
};

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

enum class CardType
{
	None = 0,
	Disturbanc, //방해 (먹물 뿌리기...) //상대 턴에만
	Passive, //패시브 (노래변경...) //게임 내에 지속
	Active, //엑티브 (자신에게 유리) //사용 순간만 
};