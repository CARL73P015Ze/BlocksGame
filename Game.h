#pragma once
#include <vector>
#include "Block.h"
#include "HiScore.h"
#include "Player.h"


const int BOARD_WIDTH = 7;
const int BOARD_HEIGHT = 11;

const int BOARD_SIZE = BOARD_WIDTH * BOARD_HEIGHT;




typedef struct Board{
	Block blocks[BOARD_WIDTH*BOARD_HEIGHT];
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
	
	bool _FoundMatch;
	bool _GameOver;
	bool _HasOrphaned;
	float _OrphanedYpos;

	int _BlocksMatched;

	HiScoreTable _Table;
private:
	int CalculateScoreForMatches(int matches);
public:
	Board _Board;
	HiScoreTable* GetHiScoreTable();
	bool IsPlayerAvailable();
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

