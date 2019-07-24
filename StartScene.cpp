#include "StdAfx.h"
#include "StartScene.h"
#include <sstream>

CStartScene::CStartScene(CRenderer* renderer, CSceneContext* sceneContext, HiScoreTable* table){
	_Renderer = renderer;
	_SceneContext = sceneContext;
	_Table = table;
}

void CStartScene::Init(){
	title = _Renderer->GetTexture("fonts.bmp");

	title_source.x = 0;
	title_source.y = 0;
	title_source.w = 500;
	title_source.h = 160;

	title_dest.x = 0;
	title_dest.y = 0;
	title_dest.w = 500;
	title_dest.h = 160;

	_MainMenu.SetX(300);
	_MainMenu.SetY(200);
	_MainMenu.Add("Start", ON_START_EVENT);
	_MainMenu.Add("Quit", ON_QUIT_EVENT);
		
	_ConfirmMenu.SetX(300);
	_ConfirmMenu.SetY(200);
	_ConfirmMenu.Add("No", ON_CONFIRM_MENU_ITEM_NO_CLICK);
	_ConfirmMenu.Add("Yes", ON_CONFIRM_MENU_ITEM_YES_CLICKED);
	_ConfirmMenu.visible = false;

	_MainMenu.SelectFirst();

	_MainMenu.visible = true;
}

void CStartScene::OnSceneStarted(){
	_ConfirmMenu.visible = false;

	_MainMenu.visible = true;
	_MainMenu.SelectFirst();
	_CurrentMenu = &_MainMenu;
	_SceneStartedAt = SDL_GetTicks();
}

void CStartScene::OnStartEvent(){
//	_Dispatcher->Dispatch(E_SCENE_GAME);
	_SceneContext->SetActiveScene(E_SCENE_GAME);
}

void CStartScene::OnQuitEvent(){
	_MainMenu.selected_id = -1;
	_MainMenu.visible = false;

	_ConfirmMenu.selected_id = -1;
	_ConfirmMenu.visible = true;
	_ConfirmMenu.SelectFirst();

	_CurrentMenu = &_ConfirmMenu;
}

void CStartScene::OnConfirmMenuItemYesClicked(){
	_SceneContext->SetActiveScene(E_APPCLOSE);
}

void CStartScene::OnConfirmMenuItemNoClick(){
	_MainMenu.visible = true;
	_ConfirmMenu.visible = false;
	_MainMenu.SelectFirst();
	_MainMenu.visible = true;

	_CurrentMenu = &_MainMenu;
}
std::string CStartScene::GetName(){ return "START";}


void CStartScene::HandleUserInput(const ExternalEvent& e){

	_CurrentMenu->HandleEvent(e);



	if(e == E_DPAD_START_PRESS || e == E_PRIMARY_BUTTON_DOWN){
		if(_CurrentMenu == &_MainMenu){
			switch(_MainMenu.selected_id){
				case ON_START_EVENT:
					OnStartEvent(); break;
				case ON_QUIT_EVENT:
					OnQuitEvent(); break;
			}
		}else if(_CurrentMenu == &_ConfirmMenu){
			switch(_ConfirmMenu.selected_id){
				case ON_CONFIRM_MENU_ITEM_NO_CLICK:
					OnConfirmMenuItemNoClick(); break;
				case ON_CONFIRM_MENU_ITEM_YES_CLICKED:
					OnConfirmMenuItemYesClicked(); break;
			}
		}
	}
}

void CStartScene::OnLoop(){
	long now = SDL_GetTicks();
	if(now - _SceneStartedAt > 5000){
//		_SceneContext->SetActiveScene(E_SCENE_DEMO);
	}
}


void CStartScene::Render(){
	_Renderer->Clear();
	_Renderer->Render(title, &title_source, &title_dest);
	std::string str;

	int y = 405;
	for(int i=0; i < _Table->MAX_TABLE_SIZE; i++){
		std::ostringstream s;
		s<<_Table->Scores[i].Name.c_str() << " - " << _Table->Scores[i].Value;
		str = s.str();
		_Renderer->RenderString(&str, 100, y);
		y-= _Renderer->GetFontHeight();
	}

	if(_CurrentMenu->visible)
		_CurrentMenu->Render(_Renderer);

}
