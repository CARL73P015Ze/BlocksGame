#include "StdAfx.h"
#include "GameAIScene.h"



CGameAIScene::CGameAIScene(CRenderer* renderer, CEventDispatcher* dispatcher) 
								: CGameScene(renderer, dispatcher){
									_AiPlayer = new CAIPlayer(&_Player);
}

std::string CGameAIScene::GetName(){ return "DEMO";}

void CGameAIScene::HandleEvent(const ExternalEvent& e){
	// consume events
	if(e == E_DPAD_START_PRESS || e == E_PRIMARY_BUTTON_DOWN){
		_Dispatcher->Dispatch(E_SCENE_START);
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
		int t = _AiPlayer->GetTargetX();
		int f = int(GetPlayer()->getX() );
		
		if(_AiPlayer->GetTargetX() < f){
			CGameScene::HandleEvent(E_DPAD_LEFT_PRESS);
		}else if(_AiPlayer->GetTargetX() > f){
			CGameScene::HandleEvent(E_DPAD_RIGHT_PRESS);
		}else if(_AiPlayer->ShouldRotate()){
			CGameScene::HandleEvent(E_DPAD_DOWN_PRESS);
		}
		_LastMove = now;
	}
	if(IsGameOver()){
		_Dispatcher->Dispatch(E_SCENE_START);
	}else{
		CGameScene::OnLoop();
	}
}
