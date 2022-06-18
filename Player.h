#pragma once
#include <iostream>

class Player {
private:
	std::string name;
	//int score;

public:
	std::string GetName();
	void SetPlayerName(std::string nam);

	//int GetScore();
	//void SetScore(int value);
};
