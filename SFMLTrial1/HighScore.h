#pragma once
#define HS_SIZE 10
#include <iostream>
#include <fstream>

class HighScore
{
private:
	int list[10];
	int cSize;
	std::fstream file;
public:
	HighScore();
	//~HighScore();

	void readList(std::fstream &file);
	bool addScore(int score);
	void sortList(void);
	void updateList(void);

};