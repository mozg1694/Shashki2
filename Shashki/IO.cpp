#include "IO.h"

#include <iostream>
#include <string>
#include <algorithm>


IO::IO()
{
}


IO::~IO()
{
}


movePos IO::GetMove(std::string player)
{
	movePos position;
	size_t p1, p2;
	std::string line1, line2;
	bool isLine1Number = true, isLine2Number = true;

	std::cout << player << " move:" << std::endl;

	std::cin >> line1;
	std::cin >> line2;

	std::for_each(line1.cbegin(), line1.cend(), [&](char c) { if (!isdigit(c)) isLine1Number = false; });
	std::for_each(line2.cbegin(), line2.cend(), [&](char c) { if (!isdigit(c)) isLine2Number = false; });

	if (!isLine1Number || !isLine2Number)
	{
		if (line1 == "ff")
		{
			// 00 00 move is a surrender
			position.first.first = 0;
			position.first.second = 0;
			position.second.first = 0;
			position.second.second = 0;
		}
		else
		{
			// 11 11 move is a bad user input
			position.first.first = 1;
			position.first.second = 1;
			position.second.first = 1;
			position.second.second = 1;
		}
	}
	else
	{
		p1 = (size_t)std::stoi(line1);
		p2 = (size_t)std::stoi(line2);

		position.first.first = p1 / 10;
		position.first.second = p1 - 10 * position.first.first;

		position.second.first = p2 / 10;
		position.second.second = p2 - 10 * position.second.first;
	}

	return std::move(position);
}


void IO::DrawBoard(const map& board)
{
	size_t boardSize = static_cast<size_t>(sqrt(board.size()));

	std::cout << "  |";

	for (size_t k = 0; k < boardSize; k++)
	{
		std::cout << k;
		std::cout << "|";
	}

	std::cout << std::endl;

	for (size_t i = 0; i < boardSize; i++)
	{
		
		std::cout << i;
		std::cout << " |";

		for (size_t j = 0; j < boardSize; j++)
		{
			std::string cellValue = CastState(board.at(pos(i, j)).GetState());
			std::cout << cellValue;
			std::cout << "|";
		}
		std::cout << std::endl;
	}

	std::cout << std::endl;
	std::cout << std::endl;
}

void IO::PrintScore(size_t whiteScore, size_t blackScore)
{
	std::cout << "White Player score: " << whiteScore << std::endl;
	std::cout << "Black Player score: " << blackScore << std::endl << std::endl;
}

void IO::EndGame(std::string player)
{
	char c;
	std::cout << std::endl << "Game Over!" << std::endl << player << " wins!" << std::endl;

	std::cin >> c;
}


std::string IO::CastState(Cell::State state)
{
	std::string result;

	switch (state)
	{
	case Cell::State::BLACK:
		result = "B";
		break;
	case Cell::State::WHITE:
		result = "W";
		break;
	default:
		result = " ";
		break;
	}

	return std::move(result);
}
