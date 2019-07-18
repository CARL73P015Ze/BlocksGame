#include "StdAfx.h"
#include "Game.h"
#include <cstdlib>
#include <cmath>


void initBoard(Board* board)
{
	for(int row=BOARD_HEIGHT-1; row >=0; row--){
		for(int i=0; i< BOARD_WIDTH; i++){
			Block* current = &board->blocks[i+((row)*BOARD_WIDTH)];

			current->remove = false;
			current->type = EMPTY;

			if(i < BOARD_WIDTH-1)
				current->connected[RIGHT] = &board->blocks[i+1+(row*BOARD_WIDTH)];
			else
				current->connected[RIGHT] = NULL;

			if(i > 0)
				current->connected[LEFT] = &board->blocks[i-1+(row*BOARD_WIDTH)];
			else
				current->connected[LEFT] = NULL;

			if(row < BOARD_HEIGHT-1)
				current->connected[DOWN] = &board->blocks[i+((row+1)*BOARD_WIDTH)];
			else
				current->connected[DOWN] = NULL;

			if(i < BOARD_WIDTH-1 && row < BOARD_HEIGHT-1){
				current->connected[DOWN_RIGHT] = &board->blocks[i+1+((row+1)*BOARD_WIDTH)];
			}else
				current->connected[DOWN_RIGHT] = NULL;

			if(i < BOARD_WIDTH-1 && row < BOARD_HEIGHT-1){
				current->connected[DOWN_LEFT] = &board->blocks[i-1+((row+1)*BOARD_WIDTH)];
			}else
				current->connected[DOWN_LEFT] = NULL;

			if(i < BOARD_WIDTH-1 && row > 0){
				current->connected[UP_RIGHT] = &board->blocks[i+1+((row-1)*BOARD_WIDTH)];
			}else
				current->connected[UP_RIGHT] = NULL;

			if(i > 0 && row > 0){
				current->connected[UP_LEFT] = &board->blocks[i-1+((row-1)*BOARD_WIDTH)];
			}else
				current->connected[UP_LEFT] = NULL;

			if(i > 0 && row > 0){
				current->connected[UP] = &board->blocks[i+((row-1)*BOARD_WIDTH)];
			}else
				current->connected[UP] = NULL;

		}


	}
}

Game::Game(void)
{
	initBoard(&_Board);
}


Game::~Game(void)
{
}

int Game::CalculateScoreForMatches(int matches){ return (matches * 10); }

HiScoreTable* Game::GetHiScoreTable(){
	return &_Table;
}

bool Game::IsPlayerAvailable() { 
	return (!_FoundMatch && !_HasOrphaned); 
}
const int& Game::GetScore()  { return _Score; }
const int& Game::GetLevel(){ return _Level; }
Player* Game::GetPlayer() { return &_Player; }
const PlayerBlock& Game::GetNext() { return _NextBlocks; }
const bool& Game::IsGameOver(){return _GameOver;}
int Game::AddBoardPiece(int column, BlockType type){
	if(column < 0 || column >= BOARD_WIDTH)
		return 0;

	int row = BOARD_HEIGHT-1;
	Block* block;
		
	while(row >= 0){
		block = &_Board.blocks[column+(row*BOARD_WIDTH)];
		if(block->type == EMPTY){
			block->type = type;
			return 1;
		}
		row--;
	}
	return -1;
}

bool Game::find_matches(Block* block, int side){
	if(block->type == EMPTY)
		return false;

	Block* next = block->connected[side];
	int matches = 1;
	while(next != NULL){
		if(next->type == block->type){
			matches++;
		}else{
			break;
		}
		next = next->connected[side];
	}
	bool result = matches > 2;
	if(result){
		next = block;
		do{
			next->remove= true;
			next = next->connected[side];
		}while(--matches > 0);
	}
	return result;
}

bool Game::find_matches(Block* block){
	return find_matches(block, RIGHT) |
			find_matches(block, DOWN) |
			find_matches(block, DOWN_RIGHT) |
			find_matches(block, DOWN_LEFT);
}

int Game::FindMatches(){
	int found = 0;

	for(int i=0; i < BOARD_SIZE; i++){
		Block* b = &_Board.blocks[i];
		if(find_matches(b))
			found ++;
	}
	
	if(found > 0){
		_Score += CalculateScoreForMatches(found);
		if(_BlocksMatched == 10){
			_BlocksMatched = 0;
			_Level ++;
		}
		_BlocksMatched++;
	}
	return found;
}

void Game::NewGame() 
{
	_Score = 0; 
	_Level = 1; 
	_GameOver = false;
	_FoundMatch = false;
	_BlocksMatched = 0;
	RandomizeNext();
	_Player.ResetPos();
	_Player.Copy(_NextBlocks);
	RandomizeNext();
	MoveDownNormalSpeed();
	_Player._Y = 0;
	_HasOrphaned = false;

	for(int i = 0; i < BOARD_WIDTH*BOARD_HEIGHT; i++){
		_Board.blocks[i].type = EMPTY;
	}
}

bool Game::BlockAt(int column, int row){
	if(column < 0 || column >= BOARD_WIDTH)
		return false;

	Block* block = &_Board.blocks[column+(row*BOARD_WIDTH)];
		
	while(row >= 0){
		block = &_Board.blocks[column+(row*BOARD_WIDTH)];
		if(block->type != EMPTY){
			return true;
		}
		row--;
	}
	return false;
}

void Game::ShuffleUp(){
	_Player.ShuffleUp();
}

void Game::ShuffleDown(){
	_Player.ShuffleDown();
}

void Game::MoveLeft(){
	int x = _Player._X;
	int y = _Player._Y/32;
	if(_Player._X > 1){
		if(_Board.blocks[x-1+(BOARD_WIDTH*y)].type == EMPTY)
			_Player._X--;
	}else if(_Player._X == 1){
		_Player._X--;
	}
}

void Game::MoveRight(){
	int x = _Player.getX();
	int y = _Player._Y/32;
	if(_Player.getX() < 5){
		if(_Board.blocks[x+1+(BOARD_WIDTH*y)].type == EMPTY)
			_Player._X++;
	}else if (_Player.getX() == 6){
		_Player._X++;
	}
}

void Game::MainLoop(long ticks_since_last_run){

	if(_FoundMatch)
		return;
		
	bool add_to_grid = true;
	const int MIN_SPEED = 1500;
	const int MAX_SPEED = 500;

	int speed = MIN_SPEED - (100 * _Level);
		
	if(speed < MAX_SPEED)
		speed = MAX_SPEED;

	//speed == 1000 milies
	//distance per second 
		
	double v = (32.0f / speed ) * SpeedMultiplier;
	double d = (double)ticks_since_last_run * v; // 0.02133f = 32 / 1500
	double y_pos = _Player._Y + d;

	// v = d/t
	// d = v

	// 2 v = 10/5

	// d = t * v
	// 10 = 5 * 2


	int grid_y_pos = (int)y_pos/ 32;
		
	if(grid_y_pos < BOARD_HEIGHT){
		if(BlockAt(_Player._X, grid_y_pos) == EMPTY){
			_Player._Y = y_pos;
			add_to_grid = false;
		}
	}
	if(add_to_grid){
		int added = AddBoardPiece(_Player.getX(), _Player.get_blocks()->bottom); 
		if(added == 1)
			added = AddBoardPiece(_Player.getX(), _Player.get_blocks()->middle);
		if(added == 1)
			added = AddBoardPiece(_Player.getX(), _Player.get_blocks()->top);

		if(added == 1){
			_FoundMatch = FindMatches() > 0;
		}else{
			_GameOver = true;
		}

		if(!_GameOver){
			GenerateNext();
		}
		MoveDownNormalSpeed();
	}
}


const bool& Game::HasOrphaned(){
	return _HasOrphaned;
}

void Game::RemoveMatchedBlocks(){
	_HasOrphaned = false;
	for(int y=0; y< BOARD_HEIGHT; y++){
		for(int x = 0; x < BOARD_WIDTH; x++){
			Block& b = _Board.blocks[x+(BOARD_WIDTH*y)];
			if(b.remove == true){
				b.remove = false;
				b.type = EMPTY;
				_HasOrphaned = true;
			}
		}
	}
	_FoundMatch = false;
}

void Game::GenerateNext(){
	_Player._Y = 0;
	_Player.Copy(_NextBlocks);
	RandomizeNext();
}

const float& Game::GetOrphanedYpos(){
	return _OrphanedYpos;
}

void Game::ProcessOrphaned(){
	Block* current;
	bool hadOrphanedBefore = _HasOrphaned;
	_HasOrphaned = false;
	for(int x = 0; x < BOARD_WIDTH; x++){
		bool found_empty = false;

		for(int y=BOARD_HEIGHT-1; y>=0 ; y--){
			current = &_Board.blocks[x+(BOARD_WIDTH*y)];
			if(current->type == EMPTY){
				found_empty = true;
				continue;
			}
			// ok move the column down 1 block

			if(found_empty && current->connected[DOWN]->type == EMPTY){
				current->connected[DOWN]->type = current->type;
				current->type = EMPTY;
				if(current->connected[DOWN]->connected[DOWN] != NULL){
					if(current->connected[DOWN]->connected[DOWN]->type == EMPTY){	
						_HasOrphaned = true;
					}
				}
			}
		}
	}

	if(_HasOrphaned != hadOrphanedBefore){
		_FoundMatch = FindMatches() > 0;
	}
}

void Game::MoveDownFast(){
	SpeedMultiplier = 10;
}

void Game::MoveDownNormalSpeed(){
	SpeedMultiplier = 1;
}

	

void Game::RandomizeNext(){
	_NextBlocks.bottom = (BlockType)(rand() % 5 + 1);
	_NextBlocks.middle = (BlockType)(rand() % 5 + 1);
	_NextBlocks.top = (BlockType)(rand() % 5 + 1);
}