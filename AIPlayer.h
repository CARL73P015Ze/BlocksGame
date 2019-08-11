#pragma once

#include "Block.h"
#include "Player.h"

namespace game
{

static const int BLOCKS_MATCHED_SIZE = 7;
	

struct ColRanking{
	int col;
	int blocks_matched[BLOCKS_MATCHED_SIZE+1];
	int y;
};

bool IsBetterRanking(const ColRanking* potential, ColRanking* best_rank);
void AssignIfBetterRanking(const ColRanking* potential, ColRanking* best_rank);

class CAIPlayer: public Player{
private:
	int _TargetX;
	PlayerBlock _TargetBlocks;
	int _TargetRotation;
	Player* _Player;

	ColRanking CalculatePerRotation(const Board* board, PlayerBlock* pb);

public:
	bool ShouldRotate();

	CAIPlayer(Player* player);

	void CalculateMove(const Board* board);

	int& GetTargetX();

	int GetTargetRotation();

	void CalculateVerticalRankingScore(const Block* board_block, PlayerBlock* pb, ColRanking* rank);
	void CalculateHorizontalRanking(const Block* block, PlayerBlock* pbs, ColRanking* rank);
	void CalculateDiagDownRightRankingScore(const Block* board_block, PlayerBlock* pb, ColRanking* rank);
	void CalculateDiagUpRightRankingScore(const Block* board_block, PlayerBlock* pb, ColRanking* rank);
private:
	void CalculateRankingScore(const Block* board_block, BlockType type, ColRanking* rank, int dir1, int dir2);


};

}
