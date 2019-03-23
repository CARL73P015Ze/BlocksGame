#include "StdAfx.h"
#include "StartScene.h"

CStartScene::CStartScene(CRenderer* renderer, CEventDispatcher* dispatcher, HiScoreTable* table){
	_Renderer = renderer;
	_Dispatcher = dispatcher;
	_Table = table;
}

void CStartScene::Init(){
	CScene::Init();

	title = _Renderer->GetTexture("fonts.bmp");

	title_source.x = 0;
	title_source.y = 0;
	title_source.w = 500;
	title_source.h = 160;

	title_dest.x = 0;
	title_dest.y = 0;
	title_dest.w = 500;
	title_dest.h = 160;

	_OnStartCEvent = new OnStartCEvent(_Dispatcher);
	_OnQuitCEvent = new OnQuitCEvent(this);
	_MainMenu.SetX(300);
	_MainMenu.SetY(200);
	_MainMenu.Add("Start", _OnStartCEvent);
	_MainMenu.Add("Quit", _OnQuitCEvent);
		
	_OnConfirmMenuItemYesClick = new OnConfirmMenuItemYesClick(_Dispatcher);
	_OnConfirmMenuItemNoClick = new OnConfirmMenuItemNoClick(this);

	_ConfirmMenu.SetX(300);
	_ConfirmMenu.SetY(200);
	_ConfirmMenu.Add("No", _OnConfirmMenuItemNoClick);
	_ConfirmMenu.Add("Yes", _OnConfirmMenuItemYesClick);
	_ConfirmMenu.visible = false;
	_MainMenu.SelectFirst();
}

void CStartScene::OnSceneStarted(){
	_ActiveComponent = &_MainMenu;
	_MainMenu.SelectFirst();
	_SceneStartedAt = SDL_GetTicks();
}

std::string CStartScene::GetName(){ return "START";}


void CStartScene::HandleEvent(const ExternalEvent& e){
	// consume events
	if(e == E_DPAD_START_PRESS || e == E_PRIMARY_BUTTON_DOWN){
		_Dispatcher->Dispatch(E_SCENE_GAME);
	}
}

void CStartScene::OnLoop(){
	long now = SDL_GetTicks();
	if(now - _SceneStartedAt > 5000){
		_Dispatcher->Dispatch(E_SCENE_DEMO);
	}
}


void CStartScene::Render(){
	_Renderer->Clear();
	_Renderer->Render(title, &title_source, &title_dest);
	std::string str;
	int y = 405;
	_HiScoreIterator = _Table->GetScores().begin();
	while(_HiScoreIterator != _Table->GetScores().end()){
		str = "";
		str += (*_HiScoreIterator)->Name.c_str();
		str += " - ";
		str += (*_HiScoreIterator)->Value;

		_Renderer->RenderString(&str, 100, y);
		y-= _Renderer->GetFontHeight();
		_HiScoreIterator++;
	}

	_MainMenu.Render(_Renderer);
	_ConfirmMenu.Render(_Renderer);
}
