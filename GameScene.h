#pragma once
#include "Scene.h"
#include "Menu.h"
#include "Player.h"
#include "EventDispatcher.h"


class CGameScene : public CScene
{
private:
	CRenderer* _Renderer;
	SDL_Rect title_source;
	SDL_Rect title_dest;
	SDL_Texture* _Blocks;
	CMenu* _PauseMenu;
	CEvent* _QuitEvent;
	CEvent* _ResumeEvent;
	Uint32 old;
	Uint32 last;
protected:
	CEventDispatcher* _Dispatcher;
public:
	CGameScene(CRenderer* renderer, CEventDispatcher* dispatcher);
	virtual std::string GetName();
	void Init();
	void OnSceneStarted();
	virtual void HandleEvent(const ExternalEvent& e);
	SDL_Rect BlockTypeToSdlRect(BlockType type);
	void RenderBoard();
	void RenderNext();
	void RenderPlayer();
	void OnLoop();
	void Render();

	void initBoard(Board* board);


	class QuitEvent : public CEvent{
	private:
		CEventDispatcher* _Dispatcher;
	public:
		QuitEvent(	CEventDispatcher* dispatcher){
			_Dispatcher = dispatcher;
		}
		virtual void OnEvent(){
			_Dispatcher->Dispatch(E_SCENE_START);
		}
	};

	class ResumeEvent : public CEvent{
	private:
		CGameScene* _Scene;
	public:
		ResumeEvent(CGameScene* scene){
			_Scene = scene;
		}
		virtual void OnEvent(){
			_Scene->last = SDL_GetTicks();
			_Scene->_PauseMenu->visible = false;
		}
	};

protected:
	int _Score;
	int _Level;
	Player _Player;
	PlayerBlock _NextBlocks;
	

	int SpeedMultiplier;
	
	bool _FoundMatch;
	bool _GameOver;
	bool _HasOrphaned;
	float _OrphanedYpos;

	int _BlocksMatched;

private:
	int CalculateScoreForMatches(int matches);
public:
	Board _Board;
	bool IsPlayerAvailable();
	const int& GetScore();
	const int& GetLevel();
	Player* GetPlayer();
	const PlayerBlock& GetNext();
	const bool& IsGameOver();
	int AddBoardPiece(int column, BlockType type);

	int FindMatches();
	bool find_matches(Block* block, int side);
	bool find_matches(Block* block);

	void NewGame();

	bool BlockAt(int column, int row);

	void ShuffleUp();

	void ShuffleDown();

	void MoveLeft();

	void MoveRight();

	void MainLoop(long ticks_since_last_run);


	const bool& HasOrphaned();

	void RemoveMatchedBlocks();

	void GenerateNext();

	const float& GetOrphanedYpos();

	void ProcessOrphaned();

	void MoveDownFast();
	void MoveDownNormalSpeed();
	void RandomizeNext();
};

