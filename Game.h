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


