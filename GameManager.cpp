#include "GameManager.h"


GameSudoku::GameSudoku() {
	player = new Player();
	board = new Board();
	invoker = new Invoker();

	mainLoop = true;
	menuLoop = true;
	gameLoop = false;
	gameIsOver = false;

	menuValue = 0;

	data.LoadData();
	data.LoadQuestion();

	DrawMenu(menuValue);
}

char GameSudoku::GetUserInput() {
	char theInput;
	if (_kbhit()) {
		theInput = _getch();
	}
	else {
		theInput = NULL;
	}
	return theInput;
}

void GameSudoku::GetPlayerInputName() {
	system("cls");

	std::string name;
	std::cout << "\n   Input Player Name\n";
	std::cout << "   Name : "; std::cin >> name;
	
	player->SetPlayerName(name);
}

void GameSudoku::MainMenu() {
	char menuInput = GetUserInput();

	switch (menuInput)
	{
	case KEY_UP:
	case 'w':
		menuValue--;
		if (menuValue < 0) {
			menuValue = 2;
		}
		DrawMenu(menuValue);
		break;
	case KEY_DOWN:
	case 's':
		menuValue++;
		if (menuValue > 2) {
			menuValue = 0;
		}
		DrawMenu(menuValue);
		break;
	case '\r':

		switch (menuValue)
		{
		case 0:
			ResumeGame();
			menuValue = 0;
			break;
		case 1:
			NewGame();
			menuValue = 0;
			break;
		case 2:
			system("cls");
			exit(0);
			break;
		default:
			break;
		}
	default:
		break;
	}
}
void GameSudoku::DrawMenu(int value) {
	system("cls");
	switch (value)
	{
	case 0:
		std::cout << "     Resume <<<\n"
				  << "    New Game \n"
				  << "      Quit \n";
		break;
	case 1:
		std::cout << "     Resume \n"
				   << "    New Game <<<\n"
				   << "      Quit \n";
		break;
	case 2:
		std::cout << "     Resume \n"
				  << "    New Game \n"
				  << "      Quit <<<\n";
		break;
	default:
		break;
	}
}

bool GameSudoku::GetLastGameData() {
	player->SetPlayerName(data.GetLastGameName());
	if (data.GetLastGameName() == "null") {
		return false;
	}
	else {
		int count = 0;
		for (int i = 0; i < board->GetBoardSize(); i++) {
			for (int j = 0; j < board->GetBoardSize(); j++) {

				board->SetBoardData(i, j, data.GetLastGameBoard(count));

				board->SetMutableBoard(i, j, data.GetLastGameMutable(count));

				count++;
			}
		}

		return true;
	}
}
void GameSudoku::GetNewQuestionData() {
	srand(time(0));
	int questNum = rand() % 5;
	int count = 0;

	for (int i = 0; i < board->GetBoardSize(); i++) {
		for (int j = 0; j < board->GetBoardSize(); j++) {
			int dataValue = data.GetQuestion(questNum, count);

			board->SetBoardData(i, j, dataValue);

			if (dataValue != 0) {
				board->SetMutableBoard(i, j, false); // Immutable
			}
			else {
				board->SetMutableBoard(i, j, true); // Mutable
			}

			count++;
		}
	}
}

void GameSudoku::ResumeGame() {
	if (data.GetDataIsEmpty() == true) {
		data.LoadData();
	}

	if (GetLastGameData() != false) {
		menuLoop = false;
		gameLoop = true;

		board->DrawBoard();
	}
	else {
		std::cout << "\n\n No Resume Data \n\n";
	}
}
void GameSudoku::NewGame() {
	if (data.GetDataIsEmpty() == true) {
		data.LoadData();
	}

	GetPlayerInputName();

	GetNewQuestionData();

	menuLoop = false;
	gameLoop = true;

	board->DrawBoard();
}

void GameSudoku::GameManager() {
	bool wasUpdated = GameInput();

	if (wasUpdated && !gameIsOver) {
		board->DrawBoard();
		
		bool isCorrect = board->CheckBoardColumn();
		if (isCorrect == true) {
			isCorrect = board->CheckBoardRow();
		}
		if (isCorrect == true) {
			isCorrect = board->CheckBoardEach3x3();
		}

		if (isCorrect == true) {
			gameIsOver = true;
		}
	}
	else if (gameIsOver == true) {
		GameOver();
	}
}
bool GameSudoku::GameInput() {
	bool wasUpdated = false;
	char input = GetUserInput();

	int cursor0Position = board->GetCursorPosition(0);
	int cursor1Position = board->GetCursorPosition(1);

	switch (input)
	{
	case KEY_UP:
	case 'w':
		if (cursor0Position != 0) {
			cursor0Position--;
			board->SetCursorPosition(0, cursor0Position);
		}
		wasUpdated = true;
		break;
	case KEY_DOWN:
	case 's':
		if (cursor0Position != board->GetBoardSize() - 1) {
			cursor0Position++;
			board->SetCursorPosition(0, cursor0Position);
		}
		wasUpdated = true;
		break;
	case KEY_LEFT:
	case 'a':
		if (cursor1Position != 0) {
			cursor1Position--;
			board->SetCursorPosition(1, cursor1Position);
		}
		wasUpdated = true;
		break;
	case KEY_RIGHT:
	case 'd':
		if (cursor1Position != board->GetBoardSize() - 1) {
			cursor1Position++;
			board->SetCursorPosition(1, cursor1Position);
		}
		wasUpdated = true;
		break;
	case 'z':
		wasUpdated = Undo();
		break;
	case 'y':
		wasUpdated = Redo();
		break;
	case 'p':
		GamePause();
		break;
	default:
		if (input >= 48 && input <= 57) {
			if (board->GetMutableBoard(cursor0Position, cursor1Position) == true && board->GetBoardData(cursor0Position, cursor1Position) != (int)input - 48) {
				FillBoard(cursor0Position, cursor1Position, (int)input - 48);
				wasUpdated = true;
			}
		}
		break;
	}

	return wasUpdated;
}
void GameSudoku::FillBoard(int i, int j, int value) {
	FillCell* command = new FillCell(*board, i, j, value);
	command->Execute();

	invoker->PushCommand(*command);
	
	invoker->ResetUndo();
}
bool GameSudoku::Undo() {
	if (invoker->isCommandEmpty() == false) {
		Command* command = invoker->GetCommand();
		command->Undo();

		invoker->PushUndo(*command); 

		invoker->PopCommand();

		return true;
	}
	else {
		return false;
	}
}
bool GameSudoku::Redo() {
	if (invoker->isUndoEmpty() == false) {
		Command* command = invoker->GetUndo();
		command->Redo();

		invoker->PushCommand(*command);

		invoker->PopUndo();

		return true;
	}
	else {
		return false;
	}
}

void GameSudoku::GamePause() {
	data.SetLastGameName(player->GetName());
	for (int i = 0; i < board->GetBoardSize(); i++) {
		for (int j = 0; j < board->GetBoardSize(); j++) {
			data.SetLastGameBoard(board->GetBoardData(i, j));

			if (board->GetMutableBoard(i, j) == true) {
				data.SetLastGameMutable(1); // mutable
			}
			else {
				data.SetLastGameMutable(0); // immutable
			}
		}
	}

	data.SaveData();

	board->ResetBoardData();
	board->ResetCursorPosition();
	invoker->ResetCommand();
	invoker->ResetUndo();

	menuLoop = true;
	gameLoop = false;

	DrawMenu(menuValue);
}
void GameSudoku::GameOver() {
	data.SetLastGameName("null");
	for (int i = 0; i < board->GetBoardSize(); i++) {
		for (int j = 0; j < board->GetBoardSize(); j++) {
			data.SetLastGameBoard(0);
			data.SetLastGameMutable(0);
		}
	}

	data.SaveData();

	board->ResetBoardData();
	board->ResetCursorPosition();
	invoker->ResetCommand();
	invoker->ResetUndo();

	menuLoop = true;
	gameLoop = false;

	// Pause the screen
	system("pause");
	DrawMenu(menuValue);
}

void GameSudoku::Play() {
	while (mainLoop == true)
	{
		if (menuLoop == true) {
			MainMenu();
		}

		else if (gameLoop == true) {
			GameManager();
		}
	}
}