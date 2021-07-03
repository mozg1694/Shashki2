#include "Game.h"
#include <iostream>
#include <stdlib.h>


Game::Game() : mWhiteScore(0), mBlackScore(0), mLastPlayer(Player::NONE), bIsSurrender(false)
{
}


Game::~Game()
{
}

Game::Player Game::GetWinner() const
{
	Player winner(Player::NONE);

	if (bIsSurrender)
	{
		if (mLastPlayer == Player::WHITE)
		{
			winner = Player::BLACK;
		}
		else if (mLastPlayer == Player::BLACK)
		{
			winner = Player::WHITE;
		}
	}
	else
	{
		if (mWhiteScore == 15)
		{
			winner = Player::WHITE;
		}
		else if (mBlackScore == 15)
		{
			winner = Player::BLACK;
		}
	}

	return winner;
}


void Game::Start()
{
	mboard.ResetMap();
	// Check is game over
	while (GetWinner() == Player::NONE)
	{
		Board::MoveResult moveResult(Board::MoveResult::PROHIBITED);

		while (moveResult == Board::MoveResult::PROHIBITED)
		{
			// IO stuff
			bool direction = GetDirection();
			auto newMove = MakeIO();

			moveResult = mboard.MakeMove(newMove.first, newMove.second, direction);
		}

		// Cehck is ff
		if (moveResult == Board::MoveResult::FF)
		{
			bIsSurrender = true;
			break;
		}

		// Parse Move Result
		if (moveResult == Board::MoveResult::SUCCESSFUL_COMBAT)
		{
			// update score
			UpdateScore();
		}

		// update last player
		SwitchPlayer();
	}

	mIO.EndGame(CastPlayer(GetWinner()));
}


bool Game::GetDirection() const
{
	bool direction;

	switch (mLastPlayer)
	{
	case Player::WHITE:
		direction = false;
		break;
	default:
		direction = true;
		break;
	}

	return direction;
}

movePos Game::MakeIO()
{
	// Print board
	system("cls");
	mIO.PrintScore(mWhiteScore, mBlackScore);
	auto map = mboard.GetMap();
	mIO.DrawBoard(map);

	// Ask for a move
	auto newMove = mIO.GetMove(GetCurrentPlayer());

	return std::move(newMove);
}

void Game::SwitchPlayer()
{
	if (mLastPlayer == Player::WHITE)
	{
		mLastPlayer = Player::BLACK;
	}
	else
	{
		mLastPlayer = Player::WHITE;
	}
}

void Game::UpdateScore()
{
	if (mLastPlayer == Player::WHITE)
	{
		mBlackScore++;
	}
	else
	{
		mWhiteScore++;
	}
}

std::string Game::GetCurrentPlayer() const
{
	std::string player;

	if (mLastPlayer == Player::WHITE)
	{
		player = "Black";
	}
	else
	{
		player = "White";
	}

	return std::move(player);
}

std::string Game::CastPlayer(Player player) const
{
	std::string playerStr;

	switch (player)
	{
	case Player::WHITE:
		playerStr = "White player";
		break;
	default:
		playerStr = "Black player";
		break;
	}

	return playerStr;
}
