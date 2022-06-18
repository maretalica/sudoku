#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <vector>


class GameData {
private:
	std::string data, name, board, mutan, question, endQuestion,close;
	
	std::string fileName, txtData;
	int MAX;
	char temp[1000];

	bool dataIsEmpty;

	std::string questionData[5];
	int questionSum;

	std::string lastGameName;
	std::vector<int> lastGameBoard;
	std::vector<int> lastGameMutable;


public:
	GameData();

	bool GetDataIsEmpty();

	void LoadData();

	std::string GetLastGameName();
	int GetLastGameBoard(int dataNumber);
	int GetLastGameMutable(int dataNumber);

	void LoadQuestion();
	int GetQuestion(int questionNumber, int dataNumber);

	void SetLastGameName(std::string nam);
	void SetLastGameBoard(int value);
	void SetLastGameMutable(int value);

	void SaveData();
	void ResetData();
};
