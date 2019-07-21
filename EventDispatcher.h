#pragma once
#include "Scene.h"

#include <unordered_map>

class CSceneContext{
private:
	CScene* _Current;
	std::unordered_map<std::string, CScene*> _Scenes;
public:
	void SetActiveScene(const ExternalEvent& e){
		if(e == E_SCENE_START)
			_Current = _Scenes["START"];
		else if(e == E_SCENE_GAME)
			_Current = _Scenes["GAME"];
		else if(e == E_SCENE_DEMO)
			_Current = _Scenes["DEMO"];
		else if (e == E_SCENE_GAME_OVER)
			_Current = _Scenes["GAME_OVER"];
		else 
			_Current = _Scenes["GAME_SHUTDOWN"];

		_Current->OnSceneStarted();
	}

	void Add(CScene* scene){
		_Scenes[scene->GetName()] = scene;
	}

	CScene* GetCurrent(){
		return _Current;
	}
};
