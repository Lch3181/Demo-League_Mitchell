#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "Vector.h"
#include<vector>
#include <SDL_gpu.h>
#include <NFont.h>
using namespace std;

class LocalScoreLeaderboard
{
public:
	vector<string> temp;
	unsigned int i = 0;

	vector<int> ScoreLearderboard;

	NFont font;


	LocalScoreLeaderboard()
	{

	}

	void WriteFile(string fileName)
	{

		ofstream file(fileName + ".txt");

		if (file.is_open())
		{
			for (unsigned int j = 0; j < i; j++)
			{
				file << temp[j] + "\n";
			}
			file.close();
		}
		else if (file.fail())
		{
			cout << "output file error" << endl;
		}

	}
	void ReadFile(string fileName)
	{

		ifstream file(fileName + ".txt");
		if (file.is_open())
		{
			string temp1;
			while (getline(file, temp1))
			{
				temp.push_back(temp1);
				i++;
			}
			file.close();
		}
		else if (file.fail())
		{
			cout << "input file error" << endl;
			cout << "Creating a new file" << endl;
			WriteFile(fileName);
		}
	}

	void AddScore(int thing)
	{
		temp.push_back(to_string(thing));
		i++;
	}

	void GetLeaderboard()
	{
		for (unsigned int j = 0; j < i; j++)
		{
			ScoreLearderboard.push_back(stoi(temp[j]));//sting to int
		}
	}

	void SortLearderboard()
	{
		sort(ScoreLearderboard.begin(), ScoreLearderboard.end());
		reverse(ScoreLearderboard.begin(), ScoreLearderboard.end());
	}

	void Draw(GPU_Target* screen)
	{
		font.load("FreeSans.ttf", 14);
		NFont::Color white = { 255,255,255 };
		GPU_RectangleFilled(screen, 300, 100, 500, 400, SDL_Color{ 0,0,0,255 });//background
		int height = 120;
		font.draw(screen, 300, height, white, "Rank       Score");

		for (unsigned int j = 0; j < i; j++)
		{
			height += 20;
			if(j<9)
				font.draw(screen, 300, height, white, "%d             %d", j + 1, ScoreLearderboard[j]);
			else
				font.draw(screen, 300, height, white, "%d            %d", j + 1, ScoreLearderboard[j]);
		}
	}


};


