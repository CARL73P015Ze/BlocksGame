#pragma once
#include "Scene.h"
#include "Menu.h"
#include "EventDispatcher.h"

const int ON_START_EVENT=1;
const int ON_QUIT_EVENT=2;
const int ON_CONFIRM_MENU_ITEM_YES_CLICKED=3;
const int ON_CONFIRM_MENU_ITEM_NO_CLICK=4;


class CStartScene : public CScene
{
private:
	CRenderer* _Renderer;
	HiScoreTable* _Table;
	SDL_Rect title_source;
	SDL_Rect title_dest;
	SDL_Texture* title;

	CMenu _MainMenu;
	CMenu _ConfirmMenu;

	CSceneContext* _SceneContext;
	long _SceneStartedAt;
public:
	CStartScene(CRenderer* renderer, CSceneContext* context, HiScoreTable* table);
	void Init();
	void OnSceneStarted();
	virtual std::string GetName();
	virtual void HandleUserInput(const ExternalEvent& e);
	void OnLoop();
	void Render();
	void OnStartEvent();
	void OnQuitEvent();
	void OnConfirmMenuItemYesClicked();
	void OnConfirmMenuItemNoClick();
};

