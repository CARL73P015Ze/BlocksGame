#include "StdAfx.h"
#include "GameShutdown.h"


GameShutdown::GameShutdown(CRenderer* renderer)
{
}


GameShutdown::~GameShutdown(void)
{
}


void GameShutdown::Render(){}
void GameShutdown::OnSceneStarted(){}
std::string GameShutdown::GetName(){ return "GAME_SHUTDOWN";}

void GameShutdown::OnLoop(){}