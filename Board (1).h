#pragma once
#include <iostream>
#include <conio.h> 
#include <stdlib.h>
#include <stack>


class Board {
private:
	int boardSize;
	int boardData[10][10];
	bool mutableBoard[10][10]; // mutable = true = 1, immutable = false = 0
	int cursorPosition[2];

public:
	Board();

	int GetBoardSize();

	int GetBoardData(int x, int y);
	void SetBoardData(int x, int y, int value);
	void ResetBoardData();

	bool GetMutableBoard(int x, int y);
	void SetMutableBoard(int x, int y, bool value);

	int GetCursorPosition(int a);
	void SetCursorPosition(int a, int value);
	void ResetCursorPosition();

	void DrawBoard();

	bool CheckBoardColumn();
	bool CheckBoardRow();
	bool CheckBoardEach3x3();
};
