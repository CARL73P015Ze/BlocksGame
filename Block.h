#pragma once



enum BlockType {EMPTY, RED, GREEN, ORANGE, BLUE, YELLOW, PURPLE};
const int DOWN = 0;
const int RIGHT = 1;
const int LEFT = 2;
const int DOWN_RIGHT = 3;
const int DOWN_LEFT = 4;
const int UP_RIGHT = 5;
const int UP_LEFT = 6;
const int UP = 7;

const int BOARD_WIDTH = 7;
const int BOARD_HEIGHT = 11;

const int BOARD_SIZE = BOARD_WIDTH * BOARD_HEIGHT;



class Block
{
public:
	BlockType type;
	bool remove;
	Block();
	~Block();
	Block* connected[8];
};


class Board{
public:
	Block blocks[BOARD_WIDTH*BOARD_HEIGHT];
	Board();
	~Board();
};





