#include "GameData.h"

GameData::GameData() {
	dataIsEmpty = true;

	data = "<Data>";
	name = "<Name>";
	board = "<Board>";
	mutan = "<Mutable>";
	question = "<Question>";
	endQuestion = "<EndQuestion>";
	close = "<Close>";

	fileName = "Game_Data.txt";
	MAX = 1000;

	questionSum = 5;
}

bool GameData::GetDataIsEmpty() {
	return dataIsEmpty;
}

void GameData::LoadData() {
	// Open 
	std::ifstream file(fileName);
	if (!file) {
		std::cout << "Error In Opening File!!!\n";
		exit(0);
	}

	// Copy
	while (!file.eof()) {
		file.getline(temp, MAX);
		txtData = txtData + temp;
	}

	// Close
	file.close();

	dataIsEmpty = false;
}

std::string GameData::GetLastGameName() {
	int findFront = 0, findBack = 0, lenght;
	std::string dataName;

	findFront = txtData.find(name, findFront) + name.size();
	findBack = txtData.find(board, findBack);
	lenght = findBack - findFront;
	dataName = txtData.substr(findFront, lenght);

	return dataName;
}
int GameData::GetLastGameBoard(int dataNumber) {
	int findFront = 0;

	findFront = txtData.find(board, findFront + 1) + board.size() + dataNumber;
	int data = stoi(txtData.substr(findFront, 1));//

	return data;
}
int GameData::GetLastGameMutable(int dataNumber) {
	int findFront = 0;

	findFront = txtData.find(mutan, findFront + 1) + mutan.size() + dataNumber;
	int data = stoi(txtData.substr(findFront, 1));

	return data;
}

void GameData::LoadQuestion() {
	int findFront = 0, findBack = 0, lenght;

	for (int i = 0; i < questionSum; i++) {
		findFront = txtData.find(question, findFront + 1) + question.size();
		findBack = txtData.find(endQuestion, findBack + 1);
		lenght = findBack - findFront;
		questionData[i] = txtData.substr(findFront, lenght);
	}
}
int GameData::GetQuestion(int questionNumber, int dataNumber) {
	int data = stoi(questionData[questionNumber].substr(dataNumber, 1));
	return data;
}

void GameData::SetLastGameName(std::string nam) {
	lastGameName = nam;
}
void GameData::SetLastGameBoard(int value) {
	lastGameBoard.push_back(value);
}
void GameData::SetLastGameMutable(int value) {
	lastGameMutable.push_back(value);
}

void GameData::SaveData() {
	// Open
	std::ofstream file(fileName);

	file << data << std::endl;

	file << name << lastGameName;
	file << board;
	for (int i = 0; i < lastGameBoard.size(); i++) {
		file << std::to_string(lastGameBoard[i]);
	}
	file << mutan;
	for (int i = 0; i < lastGameMutable.size(); i++) {
		file << std::to_string(lastGameMutable[i]);
	}
	file << std::endl;

	for (int i = 0; i < questionSum; i++) {
		file << question << questionData[i] << endQuestion << std::endl;
	}

	file << close;

	file.close();

	ResetData();
}
void GameData::ResetData() {
	txtData = "";

	lastGameName = "";
	lastGameBoard.clear();
	lastGameMutable.clear();

	dataIsEmpty = true;
}
