#pragma once

enum ExternalEvent
{
   // Mouse button events. Each of the next six events gets passed
  // the absolute position of the mouse
  E_MOUSELEFTBUTTONPRESS, 
  E_MOUSELEFTBUTTONRELEASE,

  // Start new games
  E_NEWGAMEEASY,
  E_NEWGAMENORMAL,
  E_NEWGAMEHARD,

  // Game play related
  E_INCREMENTSCORE,
  E_PAUSEGAME,
  E_CONTINUEGAME,
  E_GAMEOVER,

  // Close the App
  E_APPCLOSE,
  //E_CHANGE_SCENE,
  E_SCENE_START,
  E_SCENE_GAME,
  E_SCENE_GAME_OVER,
  E_SCENE_DEMO,

  E_PRIMARY_BUTTON_DOWN,
  E_PRIMARY_BUTTON_UP,
 // E_SECONDARY_BUTTON_DOWN,
//  E_SECONDARY_BUTTON_UP,
  E_DPAD_UP_PRESS,
  E_DPAD_DOWN_PRESS,
  E_DPAD_LEFT_PRESS,
  E_DPAD_RIGHT_PRESS,
  E_DPAD_START_PRESS
};

class CComponent{
public:
	virtual void HandleEvent(const ExternalEvent& e) = 0;
};
