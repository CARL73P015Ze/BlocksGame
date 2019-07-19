#pragma once
#include "Scene.h"

#include <unordered_map>

class CSceneMediator{
private:
	CScene* _Current;
	std::unordered_map<std::string, CScene*> _Scenes;
public:
	void HandleEvents(const ExternalEvent& e){
		if(e == E_SCENE_START){
			_Current = _Scenes["START"];
			_Current->OnSceneStarted();
		}else if(e == E_SCENE_GAME){
			_Current = _Scenes["GAME"];
			_Current->OnSceneStarted();
		}else if(e == E_SCENE_DEMO){
			_Current = _Scenes["DEMO"];
			_Current->OnSceneStarted();
		}else if (e == E_SCENE_GAME_OVER){
			_Current = _Scenes["GAME_OVER"];
			_Current->OnSceneStarted();
		}else{
			_Current->HandleEvent(e);
		}
	}

	void Add(CScene* scene){
		_Scenes[scene->GetName()] = scene;
	}

	CScene* GetCurrent(){
		return _Current;
	}
};

class CEventDispatcher{
private:
	CSceneMediator* _ActiveScene;
	bool* _Quit;
public:
	CEventDispatcher(CSceneMediator* activeScene, bool* quit){
		_ActiveScene = activeScene;
		_Quit = quit;
	}

	void Dispatch(const ExternalEvent& e){
		if(e == E_APPCLOSE){
			*_Quit = true;
		}else{
			_ActiveScene->HandleEvents(e);
		}
	}
};