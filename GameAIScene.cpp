#include "StdAfx.h"
#include "GameAIScene.h"

using namespace game;

CGameAIScene::CGameAIScene(CRenderer* renderer, CSceneContext* context) 
								: CGameScene(renderer, context){
									_AiPlayer = new CAIPlayer(&_Player);
}

std::string CGameAIScene::GetName(){ return "DEMO";}

void CGameAIScene::HandleUserInput(const ExternalEvent& e){
	// consume events
	if(e == E_DPAD_START_PRESS || e == E_PRIMARY_BUTTON_DOWN){
		_SceneContext->SetActiveScene(E_SCENE_START);
	}else
	{
		if(e == E_DUMP_STATE) {
			printf("PLAYER: \n");
			printf("%i\n%i\n%i\n", 
						this->GetPlayer()->Blocks.top,
						this->GetPlayer()->Blocks.middle,
						this->GetPlayer()->Blocks.bottom
						);

			const Block *block;
			for(int y=0; y< BOARD_HEIGHT; y++){
				for(int x = 0; x < BOARD_WIDTH-1; x++){
					block = &_Board.blocks[x+(BOARD_WIDTH*y)];

					printf("%i", block->type);
				}
				printf("\n");
			}
			

		}
	}
}

void CGameAIScene::OnSceneStarted(){
	_LastMove = SDL_GetTicks();
	CGameScene::OnSceneStarted();
}

void CGameAIScene::OnLoop(){
	long now = SDL_GetTicks(); 
		
	// if new block
	if(GetPlayer()->getY() < 10){ // needs putting on an event
		_AiPlayer->CalculateMove(&_Board);
	}
	if(now - _LastMove > 1000){
		int f = int(GetPlayer()->getX() );
		
		if(_AiPlayer->GetTargetX() < f){
			CGameScene::HandleUserInput(E_DPAD_LEFT_PRESS);
		}else if(_AiPlayer->GetTargetX() > f){
			CGameScene::HandleUserInput(E_DPAD_RIGHT_PRESS);
		}else if(_AiPlayer->ShouldRotate()){
			CGameScene::HandleUserInput(E_DPAD_DOWN_PRESS);
		}
		_LastMove = now;
	}
	if(IsGameOver()){
		_SceneContext->SetActiveScene(E_SCENE_START);
	}else{
		CGameScene::OnLoop();
	}
}
