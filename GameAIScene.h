#pragma once
#include "gamescene.h"
#include "AIPlayer.h"

class CGameAIScene : public CGameScene{
private:
	CAIPlayer* _AiPlayer;
	long _LastMove;
public:
	virtual std::string GetName();

	CGameAIScene(CRenderer* renderer, CEventDispatcher* dispatcher, Game* game);

	virtual void HandleEvent(const ExternalEvent& e);

	void OnSceneStarted();

	void OnLoop();

};