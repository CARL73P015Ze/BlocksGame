#pragma once
#include "Scene.h"
#include "Component.h"
#include "EventDispatcher.h"

class COnStringEvent{
public:
	virtual void OnEvent(std::string str) = 0;
};

class CAlphabetInput : public CComponent
{
private:
	std::string _InputtedString;
	char _SelectedCharacter;
	int _SelectedCommand;
	int _Row;
	COnStringEvent* _CompleteEvent;
public:
	bool visible;
	 CAlphabetInput(COnStringEvent* completeEvent){
		 Clear();
		 visible = true;
		 _CompleteEvent = completeEvent;
	 }

	 void Clear(){
		 _InputtedString = "";
		 _Row = 0;
		 _SelectedCommand = 1;
		 _SelectedCharacter = 'a';
	 }
	void HandleEvent(const ExternalEvent& e){
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
					_CompleteEvent->OnEvent(_InputtedString);
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

	void Render(CRenderer* renderer){
		if(!visible)
			return;
	
		std::string str = "ABCDEFGHIJKLMNOPQRSTUVWXYZ ";

		renderer->RenderString(&_InputtedString, 50, 100);
		renderer->RenderString(&str, 50, 125);


		str = "OK  DEL";
		renderer->RenderString(&str, 50, 150);


		str = "_";
		if(_Row == 0){
			renderer->RenderString(&str, 50 + ((_SelectedCharacter-'a')*10), 105);
		}else{
			renderer->RenderString(&str, 50 + (_SelectedCommand * 40), 135);
		}
	}
};


class CGameOverScene : public CScene
{
private:
	CRenderer* _Renderer;
	HiScoreTable table;
	SDL_Rect title_source;
	SDL_Rect title_dest;
	SDL_Texture* title;
	CEventDispatcher* _Dispatcher;
	HiScoreTable* _HiScoreTable;
	const int* _Score;
	COnStringEvent* _OnStringCompleteEvent; 
	bool _HasHiScore;
	CAlphabetInput* _Alphabet;
public:
	CGameOverScene(CRenderer* renderer, CEventDispatcher* dispatcher, HiScoreTable* table, const int& score);
	void Init();

	class COnStringCompleteEvent : public COnStringEvent{
	private:
		CGameOverScene* _Owner;
	public:
		COnStringCompleteEvent(CGameOverScene *owner){
			_Owner = owner;
		}

		void OnEvent(std::string str){
			int score = *_Owner->_Score;
			_Owner->_HiScoreTable->Push(score, str);
			_Owner->_Dispatcher->Dispatch(E_SCENE_START);
		}
	};

	void OnSceneStarted();

	virtual void HandleEvent(const ExternalEvent& e);

	virtual std::string GetName();

	void OnLoop();

	void Render();
};

