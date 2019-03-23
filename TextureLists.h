#pragma once
#include <string>
#include <SDL.h>
class CTextureList{
public:
	virtual SDL_Texture* GetTexture(std::string file) = 0;
};

