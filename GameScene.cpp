#include "StdAfx.h"
#include "GameScene.h"

CGameScene::CGameScene(CRenderer* renderer, CEventDispatcher* dispatcher){
		_Renderer = renderer;
		_Dispatcher = dispatcher;

	initBoard(&_Board);

	}
	//~CGameScene(void){}

std::string CGameScene::GetName(){ return "GAME";}

void CGameScene::Init(){
	CScene::Init();
	NewGame();
	_Blocks = _Renderer->GetTexture("blocks.bmp");

	title_source.x = 0;
	title_source.y = 0;
	title_source.w = 32;
	title_source.h = 32;

	title_dest.x = 32;
	title_dest.y = 32;
	title_dest.w = 32;
	title_dest.h = 32;

	_PauseMenu = new CMenu();
	_PauseMenu->SetX(100);
	_PauseMenu->SetY(100);
	_QuitEvent = new QuitEvent(_Dispatcher);
	_ResumeEvent = new ResumeEvent(this);
	_PauseMenu->Add("Resume", _ResumeEvent);
	_PauseMenu->Add("Quit", _QuitEvent);
}

void CGameScene::OnSceneStarted(){
	NewGame();
	last = SDL_GetTicks();
	_PauseMenu->visible = false;
}


void CGameScene::HandleEvent(const ExternalEvent& e){
	if(!IsGameOver()){
		if(e == E_DPAD_START_PRESS){
			_PauseMenu->visible = true;
			_PauseMenu->SelectFirst();
			_ActiveComponent = _PauseMenu;
		}else{
			CScene::HandleEvent(e);

			if(IsPlayerAvailable()){
				if(e == E_PRIMARY_BUTTON_DOWN){
					MoveDownFast();
				}else{
					MoveDownNormalSpeed();
				}
				if( e == E_DPAD_LEFT_PRESS){
					MoveLeft();
				}

				if( e == E_DPAD_RIGHT_PRESS){
					MoveRight();
				}

				if( e == E_DPAD_DOWN_PRESS){
					ShuffleDown();
				}

				if( e == E_DPAD_UP_PRESS){
					ShuffleUp();
				}
			}

		}
	}
}


SDL_Rect CGameScene::BlockTypeToSdlRect(BlockType type){
	SDL_Rect dest;
	dest.h = 32;
	dest.w = 32;
		
	dest.y = 0;
	switch(type){
		case EMPTY: dest.x = 448; break;
		case RED: dest.x = 192; break;
		case GREEN: dest.x = 128; break;
		case ORANGE: dest.x = 64; break;
		case BLUE: dest.x = 256; break;
		case YELLOW: dest.x = 0; break;
		case PURPLE: dest.x = 320; break;
	}
	return dest;
}

void CGameScene::RenderBoard(){
	
	SDL_Rect title_dest;
	SDL_Rect title_source;
	// we can animate these now.
	for(int y=0; y< BOARD_HEIGHT; y++){
		int x = 0;
		title_source = BlockTypeToSdlRect(RED);
		title_dest.w = title_source.w;
		title_dest.h = title_source.h;
		title_dest.x = (x) * title_dest.w;
		title_dest.y = (y+1) * title_dest.h;

		_Renderer->Render(_Blocks, &title_source, &title_dest);
	}


	for(int y=0; y< BOARD_HEIGHT; y++){
		int x = BOARD_WIDTH;
		title_source = BlockTypeToSdlRect(RED);
		title_dest.w = title_source.w;
		title_dest.h = title_source.h;
		title_dest.x = (x) * title_dest.w;
		title_dest.y = (y+1) * title_dest.h;

		_Renderer->Render(_Blocks, &title_source, &title_dest);
	}

	for(int x = 0; x < BOARD_WIDTH+1; x++){
		title_source = BlockTypeToSdlRect(RED);
		title_dest.w = title_source.w;
		title_dest.h = title_source.h;
		title_dest.x = x * title_dest.w;
		title_dest.y = 12 * title_dest.h;

		_Renderer->Render(_Blocks, &title_source, &title_dest);
	}
	//const Board *board = &_Game->_Board;
	const Block *block;
	for(int y=0; y< BOARD_HEIGHT; y++){
		for(int x = 0; x < BOARD_WIDTH-1; x++){
			block = &_Board.blocks[x+(BOARD_WIDTH*y)];
			title_source = BlockTypeToSdlRect(block->type);

			title_source.y = 0;
			if(block->remove){
				title_source.y = 32;
			}

			title_dest.w = title_source.w;
			title_dest.h = title_source.h;
			title_dest.x = (x+1) * title_dest.w;
			title_dest.y = (y+1) * title_dest.h;

			_Renderer->Render(_Blocks, &title_source, &title_dest);
		}
	}
}

void CGameScene::RenderNext(){
	const PlayerBlock& player = GetNext();
	SDL_Rect title_dest;
	SDL_Rect title_source;

	title_source = BlockTypeToSdlRect(player.top);
	title_dest.w = title_source.w;
	title_dest.h = title_source.h;
	title_dest.x = 510;
	title_dest.y = 45;

	_Renderer->Render(_Blocks, &title_source, &title_dest);

	title_source = BlockTypeToSdlRect(player.middle);
	title_dest.y = 45 + title_dest.h;

	_Renderer->Render(_Blocks, &title_source, &title_dest);

	title_source = BlockTypeToSdlRect(player.bottom);
	title_dest.y = 45 + 2 * title_dest.h;

	_Renderer->Render(_Blocks, &title_source, &title_dest);
}


void CGameScene::OnLoop(){
	if(_PauseMenu->visible){
		return;
	}
	Uint32 now = SDL_GetTicks();
	long ticks_since_last_run = now - last;
	last = now;
	if(IsGameOver()){
		_Dispatcher->Dispatch(E_SCENE_GAME_OVER);
	}else if(IsPlayerAvailable()){
		MainLoop(ticks_since_last_run);
		old = 0;
	}else if(HasOrphaned()){
		ProcessOrphaned();
	}else{
		old += ticks_since_last_run;
		if(old > 500){
			RemoveMatchedBlocks();
			old = 0;
		}
	}
}

void CGameScene::Render(){
	_Renderer->Clear();

	RenderBoard();
	if(IsPlayerAvailable()){
		RenderPlayer();
	}
	RenderNext();

	std::string str = "Next";
	_Renderer->RenderString(&str, 500, 20);

	str = "Score";
	_Renderer->RenderString(&str, 500, 160);

	std::stringstream outt;
	outt << GetScore();
	str = outt.str();
	_Renderer->RenderString(&str, 500, 200);
		
	str = "Level";
	_Renderer->RenderString(&str, 500, 250);
	outt.str("");
	outt.flush();
	outt.clear();
	outt << GetLevel();
	str = outt.str();
	_Renderer->RenderString(&str, 500, 270);

	if(_PauseMenu->visible)
		_PauseMenu->Render(_Renderer);
}

void CGameScene::RenderPlayer(){
	Player* player = GetPlayer();
	const PlayerBlock* blocks = player->get_blocks();
	SDL_Rect title_dest;
	SDL_Rect title_source;
	std::string output = "";

	title_source = BlockTypeToSdlRect(blocks->top);
	title_dest.w = title_source.w;
	title_dest.h = title_source.h;
	title_dest.x = (player->getX()+1) * title_dest.w;
	title_dest.y = player->_Y + -2 * title_dest.h;

	_Renderer->Render(_Blocks, &title_source, &title_dest);


	title_source = BlockTypeToSdlRect(blocks->middle);
	title_dest.w = title_source.w;
	title_dest.h = title_source.h;
	title_dest.x = (player->getX()+1) * title_dest.w;
	title_dest.y = player->_Y + -1 * title_dest.h;

	_Renderer->Render(_Blocks, &title_source, &title_dest);


	title_source = BlockTypeToSdlRect(blocks->bottom);
	title_dest.w = title_source.w;
	title_dest.h = title_source.h;
	title_dest.x = (player->getX()+1) * title_dest.w;
	title_dest.y = player->_Y + 0 * title_dest.h;

	_Renderer->Render(_Blocks, &title_source, &title_dest);
}




void CGameScene::initBoard(Board* board)
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






int CGameScene::CalculateScoreForMatches(int matches){ return (matches * 10); }

bool CGameScene::IsPlayerAvailable() { 
	return (!_FoundMatch && !_HasOrphaned); 
}
const int& CGameScene::GetScore()  { return _Score; }
const int& CGameScene::GetLevel(){ return _Level; }
Player* CGameScene::GetPlayer() { return &_Player; }
const PlayerBlock& CGameScene::GetNext() { return _NextBlocks; }
const bool& CGameScene::IsGameOver(){return _GameOver;}
int CGameScene::AddBoardPiece(int column, BlockType type){
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

bool CGameScene::find_matches(Block* block, int side){
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

bool CGameScene::find_matches(Block* block){
	return find_matches(block, RIGHT) |
			find_matches(block, DOWN) |
			find_matches(block, DOWN_RIGHT) |
			find_matches(block, DOWN_LEFT);
}

int CGameScene::FindMatches(){
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

void CGameScene::NewGame() 
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

bool CGameScene::BlockAt(int column, int row){
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

void CGameScene::ShuffleUp(){
	_Player.ShuffleUp();
}

void CGameScene::ShuffleDown(){
	_Player.ShuffleDown();
}

void CGameScene::MoveLeft(){
	int x = _Player._X;
	int y = _Player._Y/32;
	if(_Player._X > 1){
		if(_Board.blocks[x-1+(BOARD_WIDTH*y)].type == EMPTY)
			_Player._X--;
	}else if(_Player._X == 1){
		_Player._X--;
	}
}

void CGameScene::MoveRight(){
	int x = _Player.getX();
	int y = _Player._Y/32;
	if(_Player.getX() < 5){
		if(_Board.blocks[x+1+(BOARD_WIDTH*y)].type == EMPTY)
			_Player._X++;
	}else if (_Player.getX() == 6){
		_Player._X++;
	}
}

void CGameScene::MainLoop(long ticks_since_last_run){

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


const bool& CGameScene::HasOrphaned(){
	return _HasOrphaned;
}

void CGameScene::RemoveMatchedBlocks(){
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

void CGameScene::GenerateNext(){
	_Player._Y = 0;
	_Player.Copy(_NextBlocks);
	RandomizeNext();
}

const float& CGameScene::GetOrphanedYpos(){
	return _OrphanedYpos;
}

void CGameScene::ProcessOrphaned(){
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

void CGameScene::MoveDownFast(){
	SpeedMultiplier = 10;
}

void CGameScene::MoveDownNormalSpeed(){
	SpeedMultiplier = 1;
}

	

void CGameScene::RandomizeNext(){
	_NextBlocks.bottom = (BlockType)(rand() % 5 + 1);
	_NextBlocks.middle = (BlockType)(rand() % 5 + 1);
	_NextBlocks.top = (BlockType)(rand() % 5 + 1);
}