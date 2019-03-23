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

class Block
{
public:
	BlockType type;
	bool remove;

	Block();
	~Block();
	Block* connected[8];
	bool find_matches(int side){
		if(type == EMPTY)
			return false;

		Block* next = connected[side];
		int matches = 1;
		while(next != NULL){
			if(next->type == type){				
				matches++;
			}else{
				break;
			}
			next = next->connected[side];
		}
		bool result = matches > 2;
		if(result){
			next = this;
			do{
				next->remove= true;
				next = next->connected[side];
			}while(--matches > 0);
		}
		return result;
	}

	bool find_matches(){
		return find_matches(RIGHT) |
				find_matches(DOWN) |
				find_matches(DOWN_RIGHT) |
				find_matches(DOWN_LEFT);
	}

	Block* GetDown() const{ return connected[DOWN]; }
	Block* GetUp() const{ return connected[UP]; }
	Block* GetRight() const{ return connected[RIGHT]; }
	Block* GetLeft() const{ return connected[LEFT]; }
	Block* GetDiagUpRight() const{ return connected[UP_RIGHT]; } 
	Block* GetDiagDownLeft() const{ return connected[DOWN_LEFT]; }

	Block* GetDiagDownRight() const{ return connected[DOWN_RIGHT]; }
	Block* GetDiagUpLeft() const{ return connected[UP_LEFT]; }

	
};