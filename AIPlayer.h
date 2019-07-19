#pragma once

#include "Block.h"
#include "Game.h"
#include "GameScene.h"

struct ColRanking{
	int column;
	int fullRanking;
	int partialRanking;
};

class CAIPlayer: public Player{
private:
	int _TargetX;
	PlayerBlock _TargetBlocks;
	int _TargetRotation;
	Player* _Player;

	ColRanking InnerCalculateMove(const Board* board);

public:
	bool ShouldRotate();

	CAIPlayer(Player* player);

	void CalculateMove(const Board* board);

	int& GetTargetX();

	int GetTargetRotation();

	int CalculateVerticalRanking(const Block* block);

	ColRanking CalculateHorizontalRanking(const Block* block);

	void AssignRanking(ColRanking& rank, int ranking);

	int CalculateHorizontalRanking(const Block* block, BlockType& type);

	ColRanking CalculateDiagUpRight(const Block* block);

	int CalculateDiagUpRight(const Block* block, BlockType& type);

	ColRanking CalculateDiagDownRight(const Block* block);

	int CalculateDiagDownRight(const Block* block, BlockType& type);

	ColRanking CalculateColumnRating(int col, const Board* board);

	int Calculate(const Block* block, BlockType& type, int direction);
};

