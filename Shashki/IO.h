#pragma once

#include <utility>
#include <map>
#include "Cell.h"
#include <string>


using movePos = std::pair<pos, pos>;
using map = std::map<pos, Cell>;

class IO
{
public:
	IO();
	~IO();
	movePos GetMove(std::string player);
	void DrawBoard(const map& board);
	void PrintScore(size_t whiteScore, size_t blackScore);
	void EndGame(std::string player);
private:
	std::string CastState(Cell::State state);
};

