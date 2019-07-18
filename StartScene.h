#pragma once
#include "Scene.h"
#include "Menu.h"
#include "EventDispatcher.h"

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

	CEventDispatcher* _Dispatcher;
	CEvent* _OnStartCEvent;
	CEvent* _OnQuitCEvent;
	CEvent* _OnConfirmMenuItemYesClick;
	CEvent* _OnConfirmMenuItemNoClick;

	long _SceneStartedAt;
public:
	CStartScene(CRenderer* renderer, CEventDispatcher* dispatcher, HiScoreTable* table);
	void Init();
	void OnSceneStarted();
	virtual std::string GetName();
	virtual void HandleEvent(const ExternalEvent& e);
	void OnLoop();
	void Render();


	class OnStartCEvent : public CEvent{
		CEventDispatcher* _Dispatcher;
	public:
		OnStartCEvent(CEventDispatcher* dispatcher){
			_Dispatcher = dispatcher;
		}
		virtual void OnEvent(){
			_Dispatcher->Dispatch(E_SCENE_GAME);
		}
	};

	class OnQuitCEvent : public CEvent{
		CStartScene* _StartScene;
	public:
		OnQuitCEvent(CStartScene* startScene){
			_StartScene = startScene;
		}
		virtual void OnEvent(){
			_StartScene->_MainMenu.visible = false;
			_StartScene->_ConfirmMenu.visible = true;
			_StartScene->_ActiveComponent = &_StartScene->_ConfirmMenu;
			_StartScene->_ConfirmMenu.SelectFirst();
		}
	};

	class OnConfirmMenuItemYesClick : public CEvent{
		CEventDispatcher* _Dispatcher;
	public:
		OnConfirmMenuItemYesClick(CEventDispatcher* dispatcher){
			_Dispatcher = dispatcher;
		}
		virtual void OnEvent(){
			_Dispatcher->Dispatch(E_APPCLOSE);
		}
	};

	class OnConfirmMenuItemNoClick : public CEvent{
		CStartScene* _StartScene;
	public:
		OnConfirmMenuItemNoClick(CStartScene* startScene){
			_StartScene = startScene;
		}
		virtual void OnEvent(){
			_StartScene->_MainMenu.visible = true;
			_StartScene->_ConfirmMenu.visible = false;
			_StartScene->_ActiveComponent = &_StartScene->_MainMenu;
		}
	};


};

