#pragma once
#include "gamescene.h"
#include "AIPlayer.h"

namespace game
{

class CGameAIScene : public CGameScene{
private:
	CAIPlayer* _AiPlayer;
	long _LastMove;
public:
	virtual std::string GetName();

	CGameAIScene(CRenderer* renderer, CSceneContext* context);

	virtual void HandleUserInput(const ExternalEvent& e);

	void OnSceneStarted();

	void OnLoop();

};

}