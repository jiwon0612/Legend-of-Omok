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
	Normal, Rare, Unique, Legendary
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