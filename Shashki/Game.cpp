#include "Game.h"
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <list>

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

Move Game::FakeGame(size_t depth)
{
	std::cout << depth;
	Move best_move;
	Move cur_move;
	Move cur_score;
	best_move.wscore = mWhiteScore;
	best_move.bscore = mBlackScore;

	if (depth == 0) {
		return best_move;
	}

	std::list<pos> variants;
	if (GetCurrentPlayer() == "Black") {
		for (auto const& x : mboard.GetMap()) {
			if (x.second.GetState() == Cell::State::BLACK) {
				variants.push_back(x.first);
			}
		}
	}
	else {
		for (auto const& x : mboard.GetMap()) {
			if (x.second.GetState() == Cell::State::WHITE) {
				variants.push_back(x.first);
			}
		}
	}
	for (auto const& x : variants) {
		cur_move.start_pos = x;
		
		Board::MoveResult moveResult(Board::MoveResult::PROHIBITED);
		std::list<pos> moves;

		if (GetCurrentPlayer() == "Black") {
			moves.push_back(pos(x.first - 1, x.second - 1));
			moves.push_back(pos(x.first - 1, x.second + 1));
			moves.push_back(pos(x.first - 2, x.second - 2));
			moves.push_back(pos(x.first - 2, x.second + 2));
		}
		else {
			moves.push_back(pos(x.first + 1, x.second - 1));
			moves.push_back(pos(x.first + 1, x.second + 1));
			moves.push_back(pos(x.first + 2, x.second - 2));
			moves.push_back(pos(x.first + 2, x.second + 2));
		}

		for (const auto& move : moves)
		{
			bool direction = GetDirection();
			cur_move.end_pos = move;
			moveResult = mboard.MakeMove(x, move, direction);
			if (moveResult == Board::MoveResult::PROHIBITED) {
				continue;
			}

			// Parse Move Result
			if (moveResult == Board::MoveResult::SUCCESSFUL_COMBAT)
			{
				// update score
				UpdateScore();
			}

			// update last player
			SwitchPlayer();
			cur_score = FakeGame(depth - 1);
			if (GetCurrentPlayer() == "White") {
				if (cur_score.bscore > best_move.bscore) {
					best_move.bscore = cur_score.bscore;
					best_move.wscore = cur_score.wscore;
					best_move.start_pos = cur_move.start_pos;
					best_move.end_pos = cur_move.end_pos;
				}
			}
			else {
				if (cur_score.wscore < best_move.wscore) {
					best_move.bscore = cur_score.bscore;
					best_move.wscore = cur_score.wscore;
					best_move.start_pos = cur_move.start_pos;
					best_move.end_pos = cur_move.end_pos;
				}
			}
		}
	}
	std::cout << best_move.bscore;
	std::cout << std::endl;
	std::cout << best_move.wscore;
	std::cout << std::endl;
	return best_move;
}

void Game::Start()
{
	Move test;
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
