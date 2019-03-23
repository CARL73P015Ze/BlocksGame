#pragma once

#include "Block.h"

struct PlayerBlock
{
	BlockType top;
	BlockType middle;
	BlockType bottom;
};

class Player
{
public:
	void Copy(PlayerBlock& blocks){
		Blocks.top = blocks.top;
		Blocks.middle = blocks.middle;
		Blocks.bottom = blocks.bottom;
	}
	PlayerBlock Blocks;

	float _X;
	float _Y;


	void ResetPos(){
		_X = 3;
	}

	const float& getX(){
		return _X;
	}

	const float& getY(){
		return _Y;
	}

	const PlayerBlock* get_blocks(){
		return &Blocks;
	}
	void ShuffleUp(){
		BlockType temp = Blocks.top;
		Blocks.top = Blocks.bottom;
		Blocks.bottom = Blocks.middle;
		Blocks.middle = temp;
	}

	void ShuffleDown(){
		BlockType temp = Blocks.top;
		Blocks.top =  Blocks.middle;
		Blocks.middle = Blocks.bottom;
		Blocks.bottom = temp;
	}
};

