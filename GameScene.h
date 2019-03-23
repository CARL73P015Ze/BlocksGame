#pragma once
#include "Scene.h"
#include "Menu.h"
#include "Player.h"
#include "EventDispatcher.h"

class CPlayer : public CComponent
{
private:
	Game* _Game;
	SDL_Texture* _Blocks;
public:
	 CPlayer(Game* game){
		 _Game = game;
		 _Blocks = NULL;
	 }

	SDL_Rect BlockTypeToSdlRect(BlockType type){
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

	void HandleEvent(const ExternalEvent& e){
		if(_Game->IsPlayerAvailable()){
			if(e == E_PRIMARY_BUTTON_DOWN){
				_Game->MoveDownFast();
			}else{
				_Game->MoveDownNormalSpeed();
			}
			if( e == E_DPAD_LEFT_PRESS){
				_Game->MoveLeft();
			}

			if( e == E_DPAD_RIGHT_PRESS){
				_Game->MoveRight();
			}

			if( e == E_DPAD_DOWN_PRESS){
				_Game->ShuffleDown();
			}

			if( e == E_DPAD_UP_PRESS){
				_Game->ShuffleUp();
			}
		}
	}

	void Render(CRenderer* renderer){
		if(_Blocks == NULL) 
			_Blocks = renderer->GetTexture("blocks.bmp");
		Player* player = _Game->GetPlayer();
		const PlayerBlock* blocks = player->get_blocks();
	    SDL_Rect title_dest;
		SDL_Rect title_source;
		std::string output = "";

		title_source = BlockTypeToSdlRect(blocks->top);
		title_dest.w = title_source.w;
		title_dest.h = title_source.h;
		title_dest.x = (player->getX()+1) * title_dest.w;
		title_dest.y = player->_Y + -2 * title_dest.h;

		renderer->Render(_Blocks, &title_source, &title_dest);


		title_source = BlockTypeToSdlRect(blocks->middle);
		title_dest.w = title_source.w;
		title_dest.h = title_source.h;
		title_dest.x = (player->getX()+1) * title_dest.w;
		title_dest.y = player->_Y + -1 * title_dest.h;

		renderer->Render(_Blocks, &title_source, &title_dest);


		title_source = BlockTypeToSdlRect(blocks->bottom);
		title_dest.w = title_source.w;
		title_dest.h = title_source.h;
		title_dest.x = (player->getX()+1) * title_dest.w;
		title_dest.y = player->_Y + 0 * title_dest.h;

		renderer->Render(_Blocks, &title_source, &title_dest);
	}
};



class CGameScene : public CScene
{
private:
	CRenderer* _Renderer;
	SDL_Rect title_source;
	SDL_Rect title_dest;
	SDL_Texture* _Blocks;
	CMenu* _PauseMenu;
	CEvent* _QuitEvent;
	CEvent* _ResumeEvent;
	Uint32 old;
	Uint32 last;
	CPlayer* _player;
protected:
	CEventDispatcher* _Dispatcher;
	Game* _Game; 
public:
	CGameScene(CRenderer* renderer, CEventDispatcher* dispatcher, Game* game);
	virtual std::string GetName();
	void Init();
	void OnSceneStarted();
	virtual void HandleEvent(const ExternalEvent& e);
	SDL_Rect BlockTypeToSdlRect(BlockType type);
	void RenderBoard();
	void RenderNext();
	void OnLoop();
	void Render();


	class QuitEvent : public CEvent{
	private:
		CEventDispatcher* _Dispatcher;
	public:
		QuitEvent(	CEventDispatcher* dispatcher){
			_Dispatcher = dispatcher;
		}
		virtual void OnEvent(){
			_Dispatcher->Dispatch(E_SCENE_START);
		}
	};

	class ResumeEvent : public CEvent{
	private:
		CGameScene* _Scene;
	public:
		ResumeEvent(CGameScene* scene){
			_Scene = scene;
		}
		virtual void OnEvent(){
			_Scene->last = SDL_GetTicks();
			_Scene->_PauseMenu->visible = false;
			_Scene->_ActiveComponent = _Scene->_player;
		}
	};

};

