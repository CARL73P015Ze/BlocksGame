#include "stdafx.h"

#include "..\Block.h"
#include "..\Player.h"
#include "..\AIPlayer.h"

#include <string>

using namespace game;
namespace TestHelper{


	std::string BoardToString(const Board* board)
	{
		std::string output = "";
		int pos = 0;
		for(int y=0; y< BOARD_HEIGHT; y++)
		{
			for(int x = 0; x < BOARD_WIDTH; x++)
			{
				pos = x+(BOARD_WIDTH*y);
				BlockType type = board->blocks[pos].type;
				char str[5] = "";
				sprintf(str, "%d", (int)type);
				output.append(str);
				//output += block_type_to_char(type);
				if(x+1 < BOARD_WIDTH)
					output += "";
			}
			
		//	output += '\n';
		}
		return output;
	}

	std::string BoardMatchesToString(const Board* board)
	{
		std::string output = "";
		for(int y=0; y< BOARD_HEIGHT; y++)
		{
			for(int x = 0; x < BOARD_WIDTH; x++)
			{
				if(board[x+(BOARD_WIDTH*y)].blocks->remove)
					output += '1';
				else
					output += ' ';
				if(x+1 < BOARD_WIDTH)
					output += ",";
			}
			
			output += '\n';
		}
		return output;
	}
	

	void GenerateBoardFromString(std::string* input, Board* board){
		Board blocks;

		int pos = 0;
		int index = 0;
		
		for(int y=0; y< BOARD_HEIGHT; y++)
		{
			for(int x = 0; x < BOARD_WIDTH; x++)
			{
				int pos = x+(BOARD_WIDTH*y);
				char c = input->at(index);
				int i = atoi(&c);
				board->blocks[pos].type = (BlockType)i;
				index++;
			}

		}
	}

	void GeneratePlayerFromString(const char* input, Player* p)
	{		
		int i;
		char c = input[0];
		
		i = atoi(&c);
		p->Blocks.top = (BlockType)i;
		c = input[1];
		i = atoi(&c);
		p->Blocks.middle = (BlockType)i;
		c = input[2];
		i = atoi(&c);
		p->Blocks.bottom = (BlockType)i;
	}

	void RotatePlayerAndGetPlayerAsString(CAIPlayer* ai, std::string* output)
	{
		int r = ai->GetTargetRotation();

		while(r > 0){
			ai->ShuffleDown();
			r--;
		}

		char s[10];

		sprintf_s(s, "%d%d%d", ai->Blocks.top, ai->Blocks.middle, ai->Blocks.bottom);

		output->append(s);
	}


};