#include "stdafx.h"

#include <string>

class Helper{
public:
	static std::string BoardToString(const std::vector<Block>* board)
	{
		std::string output = "";
		for(int y=0; y< BOARD_HEIGHT; y++)
		{
			for(int x = 0; x < BOARD_WIDTH; x++)
			{
				output += block_type_to_char(board->at(x+(BOARD_WIDTH*y)).type);
				if(x+1 < BOARD_WIDTH)
					output += ",";
			}
			
			output += '\n';
		}
		return output;
	}

	static std::string BoardMatchesToString(const std::vector<Block>* board)
	{
		std::string output = "";
		for(int y=0; y< BOARD_HEIGHT; y++)
		{
			for(int x = 0; x < BOARD_WIDTH; x++)
			{
				if(board->at(x+(BOARD_WIDTH*y)).remove)
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
	

	static Board* GenerateBoardFromString(std::string* input){
		Board *board = new Board();
		


		std::stack<BlockType> blocks;

		std::string::iterator it = input->begin();

		while(it != input->end()){
			char c = *it;
			switch(c){
			case ' ': blocks.push(EMPTY); break;
			case 'r': blocks.push(RED); break;
			case 'g': blocks.push(GREEN);break;
			case 'b': blocks.push(BLUE);break;
			case 'y': blocks.push(YELLOW);break;
			case 'o': blocks.push(ORANGE);break;
			default: break;
			}

			it++;
		}

		int pos = blocks.size()-1;
		while(blocks.size() > 0){
			board->at(pos).type = blocks.top();
			blocks.pop();
			pos--;
		}
		return board;
	}

	static char block_type_to_char(const BlockType& type)
	{
		switch(type){
		case RED: return 'r';
		case GREEN: return 'g';
		case ORANGE:return 'o';
		case BLUE:return 'b';
		case YELLOW:return 'y';
		case PURPLE:return 'p';
		case EMPTY: return ' ';
		default:
			return '?';
		}
	}
};