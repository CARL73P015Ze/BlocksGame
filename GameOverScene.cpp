#include "StdAfx.h"
#include "GameOverScene.h"


CGameOverScene::CGameOverScene(CRenderer* renderer, CEventDispatcher* dispatcher, HiScoreTable* table, const int& score){
	_Renderer = renderer;
	_Dispatcher = dispatcher;
	_HiScoreTable = table;
	_Score = &score;
	_OnStringCompleteEvent = new COnStringCompleteEvent(this);
}

void CGameOverScene::Init(){
	_ActiveComponent = NULL;
	_Alphabet = new CAlphabetInput(_OnStringCompleteEvent);
}

void CGameOverScene::OnSceneStarted(){	
	this->_Alphabet->Clear();
	Score* entry = _HiScoreTable->HiScorePosition(*_Score);
	 _HasHiScore = entry != NULL;
	if(entry != NULL){
		_ActiveComponent = _Alphabet;
	}else{
		_ActiveComponent = NULL;
	}
}

void CGameOverScene::HandleEvent(const ExternalEvent& e){
	if(!_HasHiScore && e == E_PRIMARY_BUTTON_UP){
		_Dispatcher->Dispatch(E_SCENE_START);
	}else{
		CScene::HandleEvent(e);
	}
}

std::string CGameOverScene::GetName(){ return "GAME_OVER";}

void CGameOverScene::OnLoop(){}

void CGameOverScene::Render(){
	_Renderer->Clear();

	std::string str;
	//Score* entry = _HiScoreTable->HiScorePosition(*_Score);
	if(_HasHiScore)// entry != NULL)
	{
		str = "Please Enter Your Name";
		_Renderer->RenderString(&str, 50, 75);
		_Alphabet->Render(_Renderer);
		str = "You Made A Hi Score!";
	}else{
		str = "You Scored ";
	}
		
	char score[25];
	sprintf_s(score, "%d", *_Score); 

	str += score;
	_Renderer->RenderString(&str, 50, 50);	
}