#include "StdAfx.h"
#include "Block.h"


Block::Block(void)
{
	connected[DOWN] = nullptr;
	connected[RIGHT] = nullptr;
	connected[DOWN_RIGHT] = nullptr;
	connected[DOWN_LEFT] = nullptr;
}


Block::~Block(void)
{
}
