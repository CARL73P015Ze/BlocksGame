#include "StdAfx.h"
#include "AIPlayer.h"




ColRanking CAIPlayer::InnerCalculateMove(const Board* board){
	ColRanking result;
	result.column = 0;
	result.fullRanking = 0;
	result.partialRanking = 0;
	// for each column
	ColRanking newrank;
	for(int col=0; col < BOARD_WIDTH; col++){
		newrank = CalculateColumnRating(col, board);
		if(newrank.fullRanking > result.fullRanking){
			result.column = col;
			result.fullRanking = newrank.fullRanking;
			result.partialRanking = newrank.partialRanking;
		}
		if(result.fullRanking == 0){
			if(newrank.partialRanking > result.partialRanking){
				result.column = col;
				result.fullRanking = newrank.fullRanking;
				result.partialRanking = newrank.partialRanking;
			}
		}
	}
	return result;
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
	ColRanking noRotation = InnerCalculateMove(board);

	this->ShuffleDown();
	ColRanking rotateOnce = InnerCalculateMove(board);
		
	this->ShuffleDown();
	ColRanking rotateTwice = InnerCalculateMove(board);

	this->ShuffleUp();
	this->ShuffleUp();
	_TargetRotation = 2;

	ColRanking* useRaking = &rotateTwice;
	if(rotateOnce.fullRanking > useRaking->fullRanking ||
		(useRaking->fullRanking == 0 && rotateOnce.partialRanking > useRaking->partialRanking )){
		useRaking = &rotateOnce;
		_TargetRotation = 1;
	}
	if(noRotation.fullRanking > useRaking->fullRanking ||
		(useRaking->fullRanking == 0 && noRotation.partialRanking > useRaking->partialRanking )){
		useRaking = &noRotation;
		_TargetRotation = 0;
	}

	_TargetX = useRaking->column;
}

int& CAIPlayer::GetTargetX(){
	return _TargetX;
}

int CAIPlayer::GetTargetRotation(){
	return _TargetX;
}

int CAIPlayer::CalculateVerticalRanking(const Block* block){
	int rank = Calculate(block, this->Blocks.bottom, DOWN);	
	if(Blocks.middle == Blocks.bottom){
		rank++;
	}

	if(Blocks.middle == Blocks.top){
		rank++;
	}
	return rank;
}

ColRanking CAIPlayer::CalculateHorizontalRanking(const Block* block){
	ColRanking rank = {0, 0, 0};
	int r = 0;

	r = CalculateHorizontalRanking(block, this->Blocks.bottom);
	AssignRanking(rank, r);

	const Block* up1 = block->connected[UP];
	if(up1 != NULL){
		r = CalculateHorizontalRanking(block->connected[UP], this->Blocks.middle);
		AssignRanking(rank, r);

		const Block* up2 = up1->connected[UP];
		if(up2 != NULL){
			r = CalculateHorizontalRanking(up2, Blocks.top);
			AssignRanking(rank, r);
		}
	}

	return rank;
}

void CAIPlayer::AssignRanking(ColRanking& rank, int ranking){
	if(ranking > 2)
		rank.fullRanking += ranking;
	else
		rank.partialRanking += ranking;
}

int CAIPlayer::CalculateHorizontalRanking(const Block* block, BlockType& type){
	return Calculate(block, type, RIGHT) + Calculate(block, type, LEFT) + 1;
}


ColRanking CAIPlayer::CalculateDiagUpRight(const Block* block){
	ColRanking rank = {0, 0, 0};
	int r = 0;

	r = CalculateDiagUpRight(block, this->Blocks.bottom);
	AssignRanking(rank, r);

	const Block* up1 = block->connected[UP];
	if(up1 != NULL){
		r = CalculateDiagUpRight(block->connected[UP], this->Blocks.middle);
		AssignRanking(rank, r);

		const Block* up2 = up1->connected[UP];
		if(up2 != NULL){
			r = CalculateDiagUpRight(up2, Blocks.top);
			AssignRanking(rank, r);
		}
	}

	return rank;
}

int CAIPlayer::CalculateDiagUpRight(const Block* block, BlockType& type){
	return Calculate(block, type, UP_RIGHT) + Calculate(block, type, DOWN_LEFT) + 1;
}


ColRanking CAIPlayer::CalculateDiagDownRight(const Block* block){
	ColRanking rank = {0, 0, 0};
	int r = 0;

	r = CalculateDiagDownRight(block, this->Blocks.bottom);
	AssignRanking(rank, r);

	const Block* up1 = block->connected[UP];
	if(up1 != NULL){
		r = CalculateDiagDownRight(block->connected[UP], this->Blocks.middle);
		AssignRanking(rank, r);

		const Block* up2 = up1->connected[UP];
		if(up2 != NULL){
			r = CalculateDiagDownRight(up2, Blocks.top);
			AssignRanking(rank, r);
		}
	}

	return rank;
}

int CAIPlayer::Calculate(const Block* block, BlockType& type, int direction){
	int ddrank = 1;
	if(block->connected[direction] != NULL &&
		block->connected[direction]->type == this->Blocks.bottom){
		ddrank++;
		// ok we found a possible match
		if(block->connected[direction]->connected[direction] != NULL &&
			block->connected[direction]->connected[direction]->type == this->Blocks.bottom){
			ddrank++;
		}
	}

	return ddrank;
}

int CAIPlayer::CalculateDiagDownRight(const Block* block, BlockType& type){
	return Calculate(block, type, DOWN_RIGHT) + Calculate(block, type, UP_LEFT) - 1;
}

ColRanking CAIPlayer::CalculateColumnRating(int col, const Board* board){
	// don't both about the last 2 blocks, since we can't place the block anyway
	// find bottom empty block in the column;
	ColRanking verticalRank = {0,0,0};
	ColRanking horizontalRank = {0,0,0};
	ColRanking diagUpRightRank = {0,0,0};
	ColRanking diagDownRightRank = {0,0,0};

	for(int y=BOARD_HEIGHT-1; y >= 2; y--){
		const Block *block = &board->blocks[col+(BOARD_WIDTH*y)];
		if(block->type == EMPTY){
			AssignRanking(verticalRank, CalculateVerticalRanking(block));
			horizontalRank = CalculateHorizontalRanking(block);
			diagUpRightRank = CalculateDiagUpRight(block);
			diagDownRightRank = CalculateDiagDownRight(block);
			break;
		}
	}

	ColRanking result;
	result.fullRanking = 0;
	result.partialRanking = 0;



	result.fullRanking += verticalRank.fullRanking;
	result.fullRanking += horizontalRank.fullRanking;
	result.fullRanking += diagUpRightRank.fullRanking;
	result.fullRanking += diagDownRightRank.fullRanking;

	result.partialRanking += verticalRank.partialRanking;
	result.partialRanking += horizontalRank.partialRanking;
	result.partialRanking += diagUpRightRank.partialRanking;
	result.partialRanking += diagDownRightRank.partialRanking;

	return result;
}
