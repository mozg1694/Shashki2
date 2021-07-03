#pragma once
#include "Board.h"
#include "IO.h"

struct Move
{
	pos start_pos;
	pos end_pos;
	size_t wscore;
	size_t bscore;
};

class Game
{
public:
	enum class Player { NONE, BLACK, WHITE };
	size_t mWhiteScore;
	size_t mBlackScore;
	Game();
	~Game();
	Player GetWinner() const;
	Move FakeGame(size_t depth);
	void Start();
	Board mboard;
private:
	bool GetDirection() const;
	movePos MakeIO();
	void SwitchPlayer();
	void UpdateScore();
	std::string GetCurrentPlayer() const;
	std::string CastPlayer(Player player) const;
	Player mLastPlayer;
	bool bIsSurrender;
	IO mIO;
	
};

