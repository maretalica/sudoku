#pragma once
#include "Board.h"
#include "Command.h"


class FillCell : public Command{
private:
	int i, j, value, undoValue;
	Board* theBoard;

public:
	FillCell() = default;
	FillCell(Board &board, int a, int b, int val);

	void Execute();
	void Undo();
	void Redo();
};
