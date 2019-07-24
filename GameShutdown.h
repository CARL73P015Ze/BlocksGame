#pragma once
#include "scene.h"


class GameShutdown :public CScene
{
public:
	GameShutdown(CRenderer* renderer);
	~GameShutdown(void);

	void Render();
	void OnSceneStarted();
	std::string GetName();

	void OnLoop();


	void Init(){};
	void HandleUserInput(const ExternalEvent& e) {};

};

