#include "StdAfx.h"
#include "HiScore.h"


HiScoreTable::HiScoreTable(void)
{
	for(int i=0; i < MAX_TABLE_SIZE; i++){
		Scores[i].Name = "ABC";
		Scores[i].Value = i*MAX_TABLE_SIZE;
	}
}


HiScoreTable::~HiScoreTable(void)
{
	// clear the memory
}

Score HiScoreTbl[10];