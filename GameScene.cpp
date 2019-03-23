#include "StdAfx.h"
#include "GameScene.h"

CGameScene::CGameScene(CRenderer* renderer, CEventDispatcher* dispatcher, Game* game){
		_Renderer = renderer;
		_Dispatcher = dispatcher;
		_Game = game;
	}
	//~CGameScene(void){}

std::string CGameScene::GetName(){ return "GAME";}

void CGameScene::Init(){
	CScene::Init();
	_Game->NewGame();
	_Blocks = _Renderer->GetTexture("blocks.bmp");

	title_source.x = 0;
	title_source.y = 0;
	title_source.w = 32;
	title_source.h = 32;

	title_dest.x = 32;
	title_dest.y = 32;
	title_dest.w = 32;
	title_dest.h = 32;

	_player = new CPlayer(_Game);
	_PauseMenu = new CMenu();
	_PauseMenu->SetX(100);
	_PauseMenu->SetY(100);
	_QuitEvent = new QuitEvent(_Dispatcher);
	_ResumeEvent = new ResumeEvent(this);
	_PauseMenu->Add("Resume", _ResumeEvent);
	_PauseMenu->Add("Quit", _QuitEvent);
}

void CGameScene::OnSceneStarted(){
	_Game->NewGame();
	last = SDL_GetTicks();
	_ActiveComponent = _player;
	_PauseMenu->visible = false;
}


void CGameScene::HandleEvent(const ExternalEvent& e){
	if(!_Game->IsGameOver()){
		if(e == E_DPAD_START_PRESS){
			_PauseMenu->visible = true;
			_PauseMenu->SelectFirst();
			_ActiveComponent = _PauseMenu;
		}else{
			CScene::HandleEvent(e);
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
	const std::vector<Block>* board = _Game->GetBoard();
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

	const Block *block;
	for(int y=0; y< BOARD_HEIGHT; y++){
		for(int x = 0; x < BOARD_WIDTH-1; x++){
			block = &board->at(x+(BOARD_WIDTH*y));
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
	const PlayerBlock& player = _Game->GetNext();
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
	if(_Game->IsGameOver()){
		_Dispatcher->Dispatch(E_SCENE_GAME_OVER);
	}else if(_Game->IsPlayerAvailable()){
		_Game->MainLoop(ticks_since_last_run);
		old = 0;
	}else if(_Game->HasOrphaned()){
		_Game->ProcessOrphaned();
	}else{
		old += ticks_since_last_run;
		if(old > 500){
			_Game->RemoveMatchedBlocks();
			old = 0;
		}
	}
}

void CGameScene::Render(){
	_Renderer->Clear();

	RenderBoard();
	if(_Game->IsPlayerAvailable()){
		_player->Render(_Renderer);
	}
	RenderNext();

	std::string str = "Next";
	_Renderer->RenderString(&str, 500, 20);

	str = "Score";
	_Renderer->RenderString(&str, 500, 160);

	std::stringstream outt;
	outt << _Game->GetScore();
	str = outt.str();
	_Renderer->RenderString(&str, 500, 200);
		
	str = "Level";
	_Renderer->RenderString(&str, 500, 250);
	outt.str("");
	outt.flush();
	outt.clear();
	outt << _Game->GetLevel();
	str = outt.str();
	_Renderer->RenderString(&str, 500, 270);

	if(_PauseMenu->visible)
		_PauseMenu->Render(_Renderer);
}
