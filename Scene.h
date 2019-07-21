#pragma once

#include "stdafx.h"
#include "Renderer.h"
#include "HiScore.h"

//#include <unordered_map>

//#include <sstream>

#include "Component.h"



class CScene{
protected:
	CComponent* _ActiveComponent;
public:
	virtual void Init(){
		_ActiveComponent = NULL;
	}

	virtual void HandleEvent(const ExternalEvent& e){
		
		if(_ActiveComponent != NULL){
			_ActiveComponent->HandleEvent(e);
		}
	}

	virtual void Render() = 0;
	virtual void OnSceneStarted() = 0;
	virtual std::string GetName() = 0;

	virtual void OnLoop() = 0;
	void Play(){
		Render();
	}
};

