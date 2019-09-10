#include "HighScore.h"

HighScore::HighScore()
{
	cSize = 0;
	for (int i = 0; i < 10; i++)
	{
		list[i] = 0;
	}
	file.open("Highscores.txt", std::ios::in);
	if(file.is_open())
		readList(file);
	file.close();
}

//precondition: file must be open
//Returns size of list
void HighScore::readList(std::fstream &file)
{
	char line[10];
	while (!file.eof())
	{
		file.getline(line, 10, ' ');
		file.getline(line, 10, '\n');
		cSize++;
		addScore(atoi(line));
		//count++;
	}

	//return count;
}

bool HighScore::addScore(int score)
{
	file.open("Highscores.txt", std::ios::trunc | std::ios::out);
	bool success = 1;
	//cSize = readSize(file);
	if(cSize < 9)
		list[cSize++] = score;
	sortList();
	updateList();
	file.close();
	return success;
}

//Only sorts csize elements
void HighScore::sortList(void)
{
	int i, j, temp, min_i;
	for (i = 0; i < cSize; i++)
	{
		min_i = i;
		for (j = i; j < cSize; j++)
		{
			if (list[j] < list[i])
			{
				min_i = j;
			}
		}
		//swap i and min
		temp = list[min_i];
		list[min_i] = list[i];
		list[i] = temp;
	}
}

void HighScore::updateList(void)
{
	//file.clear();
	for (int i = 0; i < HS_SIZE; i++)
	{
		file << i+1 << ": " << list[i] << std::endl;
	}
}