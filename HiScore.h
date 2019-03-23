#pragma once

#include <vector>

struct Score{
	unsigned int Value;
	std::string Name;
};

class HiScoreTable
{
private:

	std::vector<Score*> Scores;

public:
	const static int MAX_TABLE_SIZE = 10;
	Score* Push(unsigned int value, std::string name){
		// find the position
		std::vector<Score*>::iterator it = Scores.begin();
		int pos = MAX_TABLE_SIZE;

		while(it != Scores.end()){
			if(value > (*it)->Value){
				pos--;
			}else{
				break;
			}
			
			it++;
		}
		if(pos == MAX_TABLE_SIZE)
			return NULL;

		Score* new_score = (*Scores.begin());

		new_score->Value = value;
		new_score->Name = name;
		Scores.insert(it, new_score);
		Scores.erase(Scores.begin());
		return new_score;
	}

	int HiScorePosition(const int& value){
		std::vector<Score*>::iterator it = Scores.begin();
		int pos = MAX_TABLE_SIZE;
		int val;
		while(it != Scores.end()){
			val = (*it)->Value;
			if(value > val){
				pos--;
				it++;
			}else{
				return pos;
			}
		}
		if(pos > 0)
			return pos;
		return 0;
	}

	bool HasHighScore(const int& value){
		return HiScorePosition(value) < HiScoreTable::MAX_TABLE_SIZE;
	}
	const std::vector<Score*>& GetScores(){ return Scores; }

	HiScoreTable(void);
	~HiScoreTable(void);
};

