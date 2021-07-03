#pragma once

#include "Cell.h"
#include <map>

using map = std::map<pos, Cell>;

class Board
{
public:
	enum class MoveResult { SUCCESSFUL_MOVE, SUCCESSFUL_COMBAT, PROHIBITED, FF };
	Board();
	~Board();
	void ResetMap();
	MoveResult MakeMove(const pos &startPos, const pos &endPos, bool direction, bool forceCombat = false);
	const map& GetMap() const { return mCells; }
private:
	void MovePrediction(map map, size_t depth, size_t blackScore, size_t whiteScore);
	MoveResult CheckMove(const pos &startPos, const pos &endPos, bool direction);
	const size_t mBoardSize;
	map mCells;
};

