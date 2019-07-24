#pragma once

#include "stdafx.h"
#include "Renderer.h"
#include "Component.h"



class CScene{
public:
	virtual void Init() = 0;
	virtual void HandleUserInput(const ExternalEvent& e) = 0;
	virtual void Render() = 0;
	virtual void OnSceneStarted() = 0;
	virtual std::string GetName() = 0;
	virtual void OnLoop() = 0;
};

