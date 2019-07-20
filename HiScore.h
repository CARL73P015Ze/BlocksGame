#pragma once

#include <string>

struct Score{
	unsigned int Value;
	std::string Name;
};



class HiScoreTable
{
private:
	
	

public:
	const static int MAX_TABLE_SIZE = 10;
	Score Scores[MAX_TABLE_SIZE];

	Score* HiScorePosition(const unsigned int& newScore){
		
		int i = 0;
		bool found = false;
		for(; i < MAX_TABLE_SIZE; i++){
			if(newScore >= Scores[i].Value){
				found = true;
			}else
				break;
		}

		if(!found) {
			return NULL;
		}

		return &Scores[i];

	}

	HiScoreTable(void);
	~HiScoreTable(void);
};

