#pragma once
#include "Board.h"
#include "IO.h"

class Game
{
public:
	enum class Player { NONE, BLACK, WHITE };
	Game();
	~Game();
	Player GetWinner() const;
	void Start();
private:
	bool GetDirection() const;
	movePos MakeIO();
	void SwitchPlayer();
	void UpdateScore();
	std::string GetCurrentPlayer() const;
	std::string CastPlayer(Player player) const;
	size_t mWhiteScore;
	size_t mBlackScore;
	Player mLastPlayer;
	bool bIsSurrender;
	Board mboard;
	IO mIO;
	
};

