#pragma once
#include <vector>
#include "Block.h"
#include "HiScore.h"
#include "Player.h"


const int BOARD_WIDTH = 7;
const int BOARD_HEIGHT = 11;


class Board: public std::vector<Block>{
public:
	Board() : vector<Block>(BOARD_WIDTH*BOARD_HEIGHT){


		for(int row=BOARD_HEIGHT-1; row >=0; row--){
			for(int i=0; i< BOARD_WIDTH; i++){
				Block* current = &this->at(i+((row)*BOARD_WIDTH));

				current->remove = false;
				current->type = EMPTY;

				if(i < BOARD_WIDTH-1)
					current->connected[RIGHT] = &this->at(i+1+(row*BOARD_WIDTH));
				else
					current->connected[RIGHT] = NULL;

				if(i > 0)
					current->connected[LEFT] = &this->at(i-1+(row*BOARD_WIDTH));
				else
					current->connected[LEFT] = NULL;

				if(row < BOARD_HEIGHT-1)
					current->connected[DOWN] = &this->at(i+((row+1)*BOARD_WIDTH));
				else
					current->connected[DOWN] = NULL;

				if(i < BOARD_WIDTH-1 && row < BOARD_HEIGHT-1){
					current->connected[DOWN_RIGHT] = &this->at(i+1+((row+1)*BOARD_WIDTH));
				}else
					current->connected[DOWN_RIGHT] = NULL;

				if(i < BOARD_WIDTH-1 && row < BOARD_HEIGHT-1){
					current->connected[DOWN_LEFT] = &this->at(i-1+((row+1)*BOARD_WIDTH));
				}else
					current->connected[DOWN_LEFT] = NULL;

				if(i < BOARD_WIDTH-1 && row > 0){
					current->connected[UP_RIGHT] = &this->at(i+1+((row-1)*BOARD_WIDTH));
				}else
					current->connected[UP_RIGHT] = NULL;

				if(i > 0 && row > 0){
					current->connected[UP_LEFT] = &this->at(i-1+((row-1)*BOARD_WIDTH));
				}else
					current->connected[UP_LEFT] = NULL;

				if(i > 0 && row > 0){
					current->connected[UP] = &this->at(i+((row-1)*BOARD_WIDTH));
				}else
					current->connected[UP] = NULL;

			}


		}
	}

	virtual ~Board(){

		std::vector<Block>::~vector();
	}
};

//

class Game
{
private:
	int _Score;
	int _Level;
	Player _Player;
	PlayerBlock _NextBlocks;
	

	int SpeedMultiplier;
	Board* _Board;
	bool _FoundMatch;
	bool _GameOver;
	bool _HasOrphaned;
	float _OrphanedYpos;

	int _BlocksMatched;

	HiScoreTable _Table;
private:
	int CalculateScoreForMatches(int matches);
public:

	HiScoreTable* GetHiScoreTable();
	bool IsPlayerAvailable();
	Board* GetBoard();
	const int& GetScore();
	const int& GetLevel();
	Player* GetPlayer();
	const PlayerBlock& GetNext();
	const bool& IsGameOver();
	int AddBoardPiece(int column, BlockType type);

	int FindMatches();
	bool find_matches(Block* block, int side);
	bool find_matches(Block* block);

	void NewGame();

	bool BlockAt(int column, int row);

	void ShuffleUp();

	void ShuffleDown();

	void MoveLeft();

	void MoveRight();

	void MainLoop(long ticks_since_last_run);


	const bool& HasOrphaned();

	void RemoveMatchedBlocks();

	void GenerateNext();

	const float& GetOrphanedYpos();

	void ProcessOrphaned();

	void MoveDownFast();
	void MoveDownNormalSpeed();
	void RandomizeNext();

	Game(void);
	~Game(void);
};

