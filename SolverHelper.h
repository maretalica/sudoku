//#include <iostream>
//
//int randNum(int limit)
//{
//	return rand() % limit;
//}
//
//bool UsedInRow(int board[9][9], int row, int num)
//{
//	for (int col = 0; col < 9; col++)
//	{
//		if (board[row][col] == num)
//			return true;
//	}
//
//	return false;
//}
//
//bool UsedInCol(int board[9][9], int col, int num)
//{
//	for (int row = 0; row < 9; row++)
//	{
//		if (board[row][col] == num)
//			return true;
//	}
//
//	return false;
//}
//
//bool UsedInBox(int board[9][9], int boxStartRow, int boxStartCol, int num)
//{
//	for (int row = 0; row < 3; row++)
//	{
//		for (int col = 0; col < 3; col++)
//		{
//			if (board[row + boxStartRow][col + boxStartCol] == num)
//				return true;
//		}
//	}
//
//	return false;
//}
//
//bool isSafe(int board[9][9], int row, int col, int num)
//{
//	return !UsedInRow(board, row, num) && !UsedInCol(board, col, num) && !UsedInBox(board, row - row % 3, col - col % 3, num);
//}
//
//bool findUnassignedLoc(int board[9][9], int& row, int& col)
//{
//	for (row = 0; row < 9; row++)
//	{
//		for (col = 0; col < 9; col++)
//		{
//			if (board[row][col] == 0)
//				return true;
//		}
//	}
//}
