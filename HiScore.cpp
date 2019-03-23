#include "StdAfx.h"
#include "HiScore.h"


HiScoreTable::HiScoreTable(void)
{
	for(int i=0; i < MAX_TABLE_SIZE; i++){
		Score* s = new Score();
		s->Name = "a";
		s->Value = i*MAX_TABLE_SIZE;
		Scores.push_back(s);
	}
}


HiScoreTable::~HiScoreTable(void)
{
	// clear the memory
}
