#include "StdAfx.h"
#include "AIPlayer.h"

using namespace game;



bool game::IsBetterRanking(const ColRanking* potential, ColRanking* best_rank)
{

	//5  1 > 0
	//4  1 > 0
	//3  1 > 0
	//2  1 > 4
	//1  1 > 0


	//5  0 > 0
	//4  0 > 0
	//3  0 > 1
	//2  1 > 0
	//1  0 > 0

//	bool pIsBetter = false;


	//return res;

	int p = (potential->blocks_matched[3]) +
		(potential->blocks_matched[4]) +
		(potential->blocks_matched[5]) +
		(potential->blocks_matched[6]);
	
	int b = (best_rank->blocks_matched[3]) +
		(best_rank->blocks_matched[4]) +
		(best_rank->blocks_matched[5]) +
		(best_rank->blocks_matched[6]);

	if(p==0 && b == 0){
		// ok no full matches, so lets look at the partials
		if(potential->blocks_matched[2] >= best_rank->blocks_matched[2]) 
		{
			return potential->y > best_rank->y; // ok, so we want the lowest position on the board
		}
		
		if(potential->blocks_matched[1] >= best_rank->blocks_matched[1]) 
		{
			return potential->y > best_rank->y; // ok, so we want the lowest position on the board
		}

		return false;
	}else if(b>p) 
		return false;
	{
		// ok we got a full match, so just pick the best one...
		for(int i=6; i > 2; i--){
			if(best_rank->blocks_matched[i] > potential->blocks_matched[i]){	

				break;
			}
			else if(potential->blocks_matched[i] > 0){
				return true;
			}
		}
	}


	return false;
	
	
}

void game::AssignIfBetterRanking(const ColRanking* potential, ColRanking* best_rank)
{
	bool better = IsBetterRanking(potential, best_rank);

	if(better) 
	{
		best_rank->col = potential->col;
		best_rank->y = potential->y;
		for(int i=0; i<=BLOCKS_MATCHED_SIZE; i++)
		{
			best_rank->blocks_matched[i] = potential->blocks_matched[i];
		}
	}
}

// find best column per rotation of the players block
ColRanking CAIPlayer::CalculatePerRotation(const Board* board, PlayerBlock* pb)
{
	ColRanking best_rank;
	best_rank.y = -1;
	best_rank.col = 0;
	for(int i=0; i<=BLOCKS_MATCHED_SIZE; i++)
	{
		best_rank.blocks_matched[i] = 0;
	}
	
	// for each column
	ColRanking colRanking;
	for(int col=0; col < BOARD_WIDTH; col++)
	{
		colRanking.col = col;
		for(int i=0; i<=BLOCKS_MATCHED_SIZE; i++)
			colRanking.blocks_matched[i] = 0;

		for(int y=BOARD_HEIGHT-1; y > 3; y--)
		{
			const Block *board_block = &board->blocks[col+(BOARD_WIDTH*y)];
			if(board_block->type == EMPTY){
				colRanking.y = y;
				CalculateVerticalRankingScore(board_block, pb, &colRanking);
				// need to do the calculation for each block, 
				CalculateHorizontalRanking(board_block, pb, &colRanking);

				CalculateDiagUpRightRankingScore(board_block, pb, &colRanking);
			    CalculateDiagDownRightRankingScore(board_block, pb, &colRanking);
				break;
			}
		}
		
		AssignIfBetterRanking(&colRanking, &best_rank);
	}
	return best_rank;
}


bool CAIPlayer::ShouldRotate(){
	if(_TargetRotation > 0){
		_TargetRotation--;
		return true;
	}
	return false;
}


CAIPlayer::CAIPlayer(Player* player){
	ResetPos();
	_TargetX = 3;
	_TargetRotation= 0;
	_Player = player;
}




void CAIPlayer::CalculateMove(const Board* board){
	this->Blocks = _Player->Blocks;
	_TargetRotation = 0;
	ColRanking noRotation = CalculatePerRotation(board, &Blocks);

	this->ShuffleDown();
	ColRanking rotateOnce = CalculatePerRotation(board, &Blocks);
		
	this->ShuffleDown();
	ColRanking rotateTwice = CalculatePerRotation(board, &Blocks);

	this->ShuffleUp();
	this->ShuffleUp();
	_TargetRotation = 2;
	_TargetX = rotateTwice.col;

	ColRanking* best = &rotateTwice;

	if(IsBetterRanking(&rotateOnce, best))
	{
		_TargetRotation = 1;
		_TargetX = rotateOnce.col;
		best = &rotateOnce;
	}
	if(IsBetterRanking(&noRotation, best))
	{
		_TargetRotation = 0;
		_TargetX = noRotation.col;
	}



	//colPriorityWhenNoFullMatch

	// if no full match



}

int& CAIPlayer::GetTargetX(){
	return _TargetX;
}

int CAIPlayer::GetTargetRotation(){
	return _TargetRotation;
}

void CAIPlayer::CalculateVerticalRankingScore(const Block* board_block, 
	PlayerBlock* pb, ColRanking* rank)
{
	BlockType type = pb->bottom;
	unsigned short matched = 1;
	const Block* blk = board_block->connected[DOWN];

	for(int i=0; i < 10; i++)
	{
		if ((blk == nullptr) || (blk->type != type) )
		{
			break;
		}else if (blk->type == type)		
			matched++;

		blk = blk->connected[DOWN];
	}

	if(pb->middle == type){
		matched++;

		if(pb->top == type)
			matched++;
	}
	
	matched &= BLOCKS_MATCHED_SIZE; // ensure it fits
	rank->blocks_matched[matched] += 1;


}

void CAIPlayer::CalculateHorizontalRanking(const Block* board_block, PlayerBlock* pb, ColRanking* rank)
{
	const Block* b = board_block;

	CalculateRankingScore(b, pb->bottom, rank, LEFT, RIGHT);
	b = b->connected[UP];
	CalculateRankingScore(b, pb->middle, rank, LEFT, RIGHT);
	b = b->connected[UP];
	CalculateRankingScore(b, pb->top, rank, LEFT, RIGHT);
	b = b->connected[UP];
}

void CAIPlayer::CalculateDiagDownRightRankingScore(const Block* board_block, PlayerBlock* pb, ColRanking* rank)
{
	const Block* b = board_block;

	CalculateRankingScore(b, pb->bottom, rank, UP_LEFT, DOWN_RIGHT);
	b = b->connected[UP];
	CalculateRankingScore(b, pb->middle, rank, UP_LEFT, DOWN_RIGHT);
	b = b->connected[UP];
	CalculateRankingScore(b, pb->top, rank, UP_LEFT, DOWN_RIGHT);
	b = b->connected[UP];
}

void CAIPlayer::CalculateDiagUpRightRankingScore(const Block* board_block, PlayerBlock* pb, ColRanking* rank)
{
	const Block* b = board_block;

	CalculateRankingScore(b, pb->bottom, rank, UP_RIGHT, DOWN_LEFT);
	b = b->connected[UP];
	CalculateRankingScore(b, pb->middle, rank, UP_RIGHT, DOWN_LEFT);
	b = b->connected[UP];
	CalculateRankingScore(b, pb->top, rank, UP_RIGHT, DOWN_LEFT);
	b = b->connected[UP];
}

void CAIPlayer::CalculateRankingScore(const Block* board_block, BlockType type, ColRanking* rank, int dir1, int dir2)
{
	unsigned short matched = 1;
	const Block* blk = board_block->connected[dir1];

	for(int i=0; i < 10; i++)
	{
		if ((blk == nullptr) || (blk->type != type) )
		{
			break;
		}else if (blk->type == type)		
			matched++;

		blk = blk->connected[dir1];
	}


	blk = board_block->connected[dir2];
	
	for(int i=0; i < 10; i++)
	{
		if ((blk == nullptr) || (blk->type != type) )
		{
			break;
		}else if (blk->type == type)		
			matched++;

		blk = blk->connected[dir2];
	}

	
	matched &= BLOCKS_MATCHED_SIZE; // ensure it fits
	rank->blocks_matched[matched] += 1;
}
