#pragma once

#include <utility>

using pos = std::pair<size_t, size_t>;

class Cell
{
public:
	enum class State { BLACK, WHITE, BLANK };
	Cell(/*const pos& position,*/ State state);
	~Cell();
	State GetState() const { return mState; }
	void SetState(State state) { mState = state; }
	//const pos& GetPosition() const { return mPosition; }
	//void SetPosition(const pos& position) { mPosition = position; }
private:
	State mState;
	//pos mPosition;
};