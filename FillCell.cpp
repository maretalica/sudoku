#include "FillCell.h"


FillCell::FillCell(Board& board, int a, int b, int val) {
	theBoard = &board;
	i = a;
	j = b;
	value = val;
}

void FillCell::Execute() {
	undoValue = theBoard->GetBoardData(i, j);
	theBoard->SetBoardData(i, j, value);
}
void FillCell::Undo() {
	theBoard->SetBoardData(i, j, undoValue);
}
void FillCell::Redo() {
	theBoard->SetBoardData(i, j, value);
}
