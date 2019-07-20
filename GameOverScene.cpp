#include "StdAfx.h"
#include "GameOverScene.h"


CGameOverScene::CGameOverScene(CRenderer* renderer, CEventDispatcher* dispatcher, HiScoreTable* table, const int& score){
	_Renderer = renderer;
	_Dispatcher = dispatcher;
	_HiScoreTable = table;
	_Score = &score;
}

void CGameOverScene::Init(){
	_ActiveComponent = NULL;
}

void CGameOverScene::OnSceneStarted(){	
	Clear();
	Score* entry = _HiScoreTable->HiScorePosition(*_Score);
	 _HasHiScore = entry != NULL;
	_ActiveComponent = NULL;
}

void CGameOverScene::HandleEvent(const ExternalEvent& e){
	if(!_HasHiScore && e == E_PRIMARY_BUTTON_UP){
		_Dispatcher->Dispatch(E_SCENE_START);
	}else{

		if(_Row == 0){
			if(e == E_DPAD_LEFT_PRESS){
				if(_SelectedCharacter > 'a'){
					_SelectedCharacter--;
				}
			}
			if( e == E_DPAD_RIGHT_PRESS){
				if(_SelectedCharacter < 'z'){
					_SelectedCharacter++;
				}				
			}
			if(e == E_DPAD_DOWN_PRESS){
				_SelectedCommand = 1;
				_Row++;
			}

			if( e == E_PRIMARY_BUTTON_UP){
				_InputtedString += _SelectedCharacter;
			}
		}else if(_Row == 1){
			if(e == E_DPAD_LEFT_PRESS){
				if(_SelectedCommand > 0){
					_SelectedCommand--;
				}
			}
			if( e == E_DPAD_RIGHT_PRESS){
				if(_SelectedCommand < 1){
					_SelectedCommand++;
				}				
			}

			if( e == E_PRIMARY_BUTTON_UP){
				if(_SelectedCommand == 0){
					

				int score = *_Score;
				Score* entry= _HiScoreTable->HiScorePosition(score);
				if(entry != NULL) {
					entry->Name = _InputtedString;
					entry->Value = score;
				}
				_Dispatcher->Dispatch(E_SCENE_START);

					// save the high score and show main screen
				}else{
					// delete a character
					if(_InputtedString.size() > 0){
						_InputtedString.pop_back();
					}
				}

			}

			if(e == E_DPAD_UP_PRESS){
				_Row--;
			}
		}
	}
}

std::string CGameOverScene::GetName(){ return "GAME_OVER";}

void CGameOverScene::OnLoop(){}

void CGameOverScene::Render(){
	_Renderer->Clear();

	std::string str;
	if(_HasHiScore)
	{
		str = "Please Enter Your Name";
		_Renderer->RenderString(&str, 50, 75);
		RenderAlphabet();
		str = "You Made A Hi Score!";
	}else{
		str = "You Scored ";
	}
		
	char score[25];
	sprintf_s(score, "%d", *_Score); 

	str += score;
	_Renderer->RenderString(&str, 50, 50);	
}


void CGameOverScene::Clear(){
	_InputtedString = "";
	_Row = 0;
	_SelectedCommand = 1;
	_SelectedCharacter = 'a';
}


void CGameOverScene::RenderAlphabet(){

	
	std::string str = "ABCDEFGHIJKLMNOPQRSTUVWXYZ ";

	_Renderer->RenderString(&_InputtedString, 50, 100);
	_Renderer->RenderString(&str, 50, 125);


	str = "OK  DEL";
	_Renderer->RenderString(&str, 50, 150);


	str = "_";
	if(_Row == 0){
		_Renderer->RenderString(&str, 50 + ((_SelectedCharacter-'a')*10), 105);
	}else{
		_Renderer->RenderString(&str, 50 + (_SelectedCommand * 40), 135);
	}
}