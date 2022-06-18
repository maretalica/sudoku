#include "Board.h"


Board::Board() {
	boardSize = 9;
	ResetBoardData();
	ResetCursorPosition();
}

int Board::GetBoardSize() {
	return boardSize;
}

int Board::GetBoardData(int x, int y) {
	return boardData[x][y];
}
void Board::SetBoardData(int x, int y, int value) {
	boardData[x][y] = value;
}
void Board::ResetBoardData() {
	for (int i = 0; i < boardSize; i++) {
		for (int j = 0; j < boardSize; j++) {
			boardData[i][j] = 0;
		}
	}
}

bool Board::GetMutableBoard(int x, int y) {
	return mutableBoard[x][y];
}
void Board::SetMutableBoard(int x, int y, bool value) {
	mutableBoard[x][y] = value;
}

int Board::GetCursorPosition(int a) {
	return cursorPosition[a];
}
void Board::SetCursorPosition(int a, int value) {
	cursorPosition[a] = value;
}
void Board::ResetCursorPosition() {
	cursorPosition[0] = 0;
	cursorPosition[1] = 0;
}

void Board::DrawBoard() {
	system("cls");
	
	// Title
	std::cout << "\n                      SUDOKU";

	// Margin Top
	std::cout << "\n\n";

	for (int i = 0; i < boardSize; i++) {
		// Margin Left
		std::cout << "     ";

		if (i % 3 == 0 && i != 0) {
			std::cout << " #";
			for (int j = 0; j < boardSize; j++) {
				std::cout << "####";
			}
			std::cout << "\n";
			std::cout << "     ";
		}

		// Number
		for (int j = 0; j < boardSize; j++) {
			
			// Dividers between boxes
			if (j % 3 == 0 && j != 0) {
				std::cout << " # ";
			}
			else {
				std::cout << " | ";
			}
			
			// Box contain
			if (boardData[i][j] == 0) {
				std::cout << " ";
			}
			else {
				std::cout << boardData[i][j];
			}
		} 
		// Close Box 
		std::cout << " | ";

		// For User Interface ( right side of the screen )
		if (i == 1) {
			std::cout << "           Press p to exit";
		}
		else if (i == 3) {
			std::cout << "           Press z to undo";
		}
		else if (i == 5) {
			std::cout << "           Press y to redo";
		}

		// Next Line
		std::cout << std::endl;

		// Margin Left
		std::cout << "     ";

		// Cursor
		for (int j = 0; j < boardSize; j++) {

			// Dividers between boxes
			if (j % 3 == 0 && j != 0 && i != boardSize - 1) {
				std::cout << " # ";
			}
			else {
				std::cout << "   ";
			}

			// The Cursor
			if (cursorPosition[0] == i && cursorPosition[1] == j) {
				std::cout << "^";
			}
			else {
				std::cout << " ";
			}
		}

		// Next Line
		std::cout << std::endl;
	}
}

bool Board::CheckBoardColumn() {
	// Column
	for (int i = 0; i < boardSize; i++) {
		for (int j = 0; j < boardSize - 1; j++) {
			for (int k = j + 1; k < boardSize; k++) {
				if (boardData[i][j] == boardData[i][k]) {
					return false;
				}
			}
		}
	}
}
bool Board::CheckBoardRow() {
	// Row
	for (int i = 0; i < boardSize; i++) {
		for (int j = 0; j < boardSize - 1; j++) {
			for (int k = j + 1; k < boardSize; k++) {
				if (boardData[j][i] == boardData[k][i]) {
					return false;
				}
			}
		}
	}

	return true;
}
bool Board::CheckBoardEach3x3() {
	// Each 3x3
	for (int i = 0; i < boardSize; i += 3) {
		for (int j = 0; j < boardSize; j += 3) {
			for (int k = i; k < i + 3; k++) {
				for (int l = j; l < i + 3; l++) {
					for (int m = k; m < i + 3; m++) {
						for (int n = l; n < i + 3; n++) {
							if (k == m && l == n) {
								n++;
							}
							else {
								if (boardData[k][l] == boardData[m][n]) {
									return false;
								}
							}
						}
					}
				}
			}
		}
	}

	return true;
}



