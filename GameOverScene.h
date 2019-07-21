#pragma once
#include "Scene.h"
#include "Component.h"
#include "EventDispatcher.h"

class CGameOverScene : public CScene
{
private:
	CRenderer* _Renderer;
	HiScoreTable table;
	SDL_Rect title_source;
	SDL_Rect title_dest;
	SDL_Texture* title;
	CSceneContext* _SceneContext;
	HiScoreTable* _HiScoreTable;
	const int* _Score;
	bool _HasHiScore;
private:
	std::string _InputtedString;
	char _SelectedCharacter;
	int _SelectedCommand;
	int _Row;
public:
	CGameOverScene(CRenderer* renderer, CSceneContext* context, HiScoreTable* table, const int& score);
	void Init();

	void OnSceneStarted();

	virtual void HandleUserInput(const ExternalEvent& e);

	virtual std::string GetName();

	void OnLoop();

	void Render();

private:
	void Clear();
	void RenderAlphabet();
};

