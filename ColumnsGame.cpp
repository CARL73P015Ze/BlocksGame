// ColumnsGame2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"



#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string>
#include <SDL.h>
#include "Animation.h"
#include "Renderer.h"
#include "Renderable.h"
#include "Renderer.h"
#include "HiScore.h"
#include "Scene.h"

#include "StartScene.h"
#include "GameScene.h"
#include "GameOverScene.h"
#include "AIPlayer.h"
#include "Game.h"
#include "GameAIScene.h"

int main2();

int _tmain(int argc, _TCHAR* argv[]){
	printf("%s    ",argv[0]);
	return main2();
}


//Screen dimension constants
const int SCREEN_WIDTH = 1280;//640;
const int SCREEN_HEIGHT = 960;//480;
const char GAME_NAME[] = "Blocks";

int main2(  )
{
    if (SDL_Init(SDL_INIT_EVERYTHING) == -1){
		printf("%s", SDL_GetError());
        return 1;
    }

	SDL_Window *win = nullptr;
    win = SDL_CreateWindow(GAME_NAME, 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (win == nullptr){
		printf("%s", SDL_GetError());
        return 1;
    }

	SDL_Renderer *ren = nullptr;
    ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (ren == nullptr){
		printf("%s", SDL_GetError());
        return 1;
    }
	

	SDL_RenderSetLogicalSize(ren, 640, 480);

	FontSettings _FontSettings;
	_FontSettings.font_offset_x = 118;
	_FontSettings.font_offset_y = 204;
	_FontSettings.height = 21;
	_FontSettings.width = 10;
	_FontSettings.textureFileName = "fonts.bmp";


	CRenderer renderer(ren, _FontSettings);



	renderer.Clear();

	bool quit = false;
	CSceneMediator scenes;
	CEventDispatcher handler(&scenes, &quit);

	Game* game = new Game();
	
	CStartScene scene(&renderer, &handler, game->GetHiScoreTable());
	CGameScene game_scene(&renderer, &handler, game);
	CGameOverScene gameOverScene(&renderer, &handler, game->GetHiScoreTable(), game->GetScore());
	scene.Init();
	game_scene.Init();
	gameOverScene.Init();

	CGameAIScene demo(&renderer, &handler, game);

	demo.Init();


	scenes.Add(&scene);
	scenes.Add(&demo);
	scenes.Add(&game_scene);
	scenes.Add(&gameOverScene);
	scenes.HandleEvents(E_SCENE_START);	

    SDL_RenderPresent(ren);
	SDL_Event e;
	
	SDL_GameController *gamecontroller = NULL;
	int i;
	const int PRESSED = 1;
	for (i = 0; i < SDL_NumJoysticks(); ++i) {
		if (SDL_IsGameController(i)) {
			printf("Index \'%i\' is a compatible controller, named \'%s\'\n", i, SDL_GameControllerNameForIndex(i));
			gamecontroller = SDL_GameControllerOpen(i);
			printf("Controller %i is mapped as \"%s\".\n", i, SDL_GameControllerMapping(gamecontroller));
		} else {
			printf("Index \'%i\' is not a compatible controller.", i);
		}
	}



	bool PRIMARY_BUTTON_DOWN = false;
	while(!quit){
        if (SDL_PollEvent(&e)){

            if (e.type == SDL_QUIT)
                quit = true;

          if (e.type == SDL_KEYDOWN){
			  switch(e.key.keysym.scancode){
				case SDL_SCANCODE_SPACE: handler.Dispatch(E_PRIMARY_BUTTON_DOWN); break;
				case SDL_SCANCODE_RIGHT: handler.Dispatch(E_DPAD_RIGHT_PRESS); break;
				case SDL_SCANCODE_LEFT: handler.Dispatch(E_DPAD_LEFT_PRESS); break;
				case SDL_SCANCODE_UP: handler.Dispatch(E_DPAD_UP_PRESS); break;
				case SDL_SCANCODE_DOWN: handler.Dispatch(E_DPAD_DOWN_PRESS); break;
				case SDL_SCANCODE_ESCAPE: handler.Dispatch(E_DPAD_START_PRESS); break;
				default: break;
			  };
			}else if (e.type == SDL_KEYUP){
				switch(e.key.keysym.scancode){
					case SDL_SCANCODE_SPACE: handler.Dispatch(E_PRIMARY_BUTTON_UP); break;
				}
			}
		}

		if(gamecontroller != NULL){

			// Or space was pressed
			if(SDL_GameControllerGetButton(gamecontroller, SDL_CONTROLLER_BUTTON_A) == PRESSED){
				handler.Dispatch(E_PRIMARY_BUTTON_DOWN);
				PRIMARY_BUTTON_DOWN =true;
			}else if(PRIMARY_BUTTON_DOWN){
				handler.Dispatch(E_PRIMARY_BUTTON_UP);
				PRIMARY_BUTTON_DOWN =false;
			}

			if(SDL_GameControllerGetButton(gamecontroller, SDL_CONTROLLER_BUTTON_DPAD_LEFT) == PRESSED){
				handler.Dispatch(E_DPAD_LEFT_PRESS);
			}

			if(SDL_GameControllerGetButton(gamecontroller, SDL_CONTROLLER_BUTTON_DPAD_RIGHT) == PRESSED){
				handler.Dispatch(E_DPAD_RIGHT_PRESS);
			}

			if(SDL_GameControllerGetButton(gamecontroller, SDL_CONTROLLER_BUTTON_DPAD_UP) == PRESSED){
				handler.Dispatch(E_DPAD_UP_PRESS);
			}

			if(SDL_GameControllerGetButton(gamecontroller, SDL_CONTROLLER_BUTTON_DPAD_DOWN) == PRESSED){
				handler.Dispatch(E_DPAD_DOWN_PRESS);
			}

			if(SDL_GameControllerGetButton(gamecontroller, SDL_CONTROLLER_BUTTON_START) == PRESSED){
				handler.Dispatch(E_DPAD_START_PRESS);
			}
		}
		scenes.GetCurrent()->OnLoop();
		scenes.GetCurrent()->Play();
		SDL_RenderPresent(ren);
	}

    SDL_DestroyWindow(win);
	SDL_Quit();
    return 0;
}
