#include "StdAfx.h"
#include "Block.h"

#include <stdlib.h>

Block::Block(void)
{
	connected[DOWN] = nullptr;
	connected[RIGHT] = nullptr;
	connected[DOWN_RIGHT] = nullptr;
	connected[DOWN_LEFT] = nullptr;
	type = PURPLE;
	remove = false;
}


Block::~Block(void)
{
}


Board::Board()
{
	
	for(int y=0; y < BOARD_HEIGHT; y++){
		for(int x=0; x < BOARD_WIDTH; x++){
			int bpos = x+((y)*BOARD_WIDTH);
			Block* current = &blocks[bpos];

			current->type = EMPTY;

			if(x < BOARD_WIDTH-1)
				current->connected[RIGHT] = &blocks[bpos+1];
			else
				current->connected[RIGHT] = nullptr;

			if(x > 0)
				current->connected[LEFT] = &blocks[bpos-1];
			else
				current->connected[LEFT] = nullptr;

			if(y < BOARD_HEIGHT-1)
				current->connected[DOWN] = &blocks[bpos+BOARD_WIDTH];
			else
				current->connected[DOWN] = nullptr;

			if(x < BOARD_WIDTH-1 && y < BOARD_HEIGHT-1){
				current->connected[DOWN_RIGHT] = &blocks[bpos+1+BOARD_WIDTH];
			}else
				current->connected[DOWN_RIGHT] = nullptr;

			if(x < BOARD_WIDTH-1 && y < BOARD_HEIGHT-1){
				current->connected[DOWN_LEFT] = &blocks[bpos-1+BOARD_WIDTH];
			}else
				current->connected[DOWN_LEFT] = nullptr;

			if(x < BOARD_WIDTH-1 && y > 0){
				current->connected[UP_RIGHT] = &blocks[bpos+1-BOARD_WIDTH];
			}else
				current->connected[UP_RIGHT] = nullptr;

			if(x > 0 && y > 0){
				current->connected[UP_LEFT] = &blocks[bpos-1-BOARD_WIDTH];
			}else
				current->connected[UP_LEFT] = nullptr;

			if(y > 0){
				current->connected[UP] = &blocks[bpos-BOARD_WIDTH];
			}else
				current->connected[UP] = nullptr;

		}

	}
	
}

Board::~Board(void)
{
}



