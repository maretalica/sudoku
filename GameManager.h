#pragma once
#include <time.h>
#include <conio.h>
#include "Player.h"
#include "Board.h"
#include "GameData.h"
#include "Invoke.h"
#include "FillCell.h"

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

class GameSudoku {
private:
	GameData data;
	Player* player;
	Board* board;
	Invoker* invoker;

	bool mainLoop;
	bool menuLoop;
	bool gameLoop;
	bool gameIsOver;

	int menuValue;

	char GetUserInput();

	void GetPlayerInputName();

	void MainMenu();
	void DrawMenu(int value);

	bool GetLastGameData();
	void GetNewQuestionData();

	void ResumeGame();
	void NewGame();

	void GameManager();
	bool GameInput();
	void FillBoard(int i, int j, int value);
	bool Undo();
	bool Redo();

	void GamePause();
	void GameOver();

public:
	GameSudoku();

	void Play();
};
