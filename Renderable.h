#pragma once
#include <string>
#include <SDL.h>
#include <vector>

struct Frame{
	SDL_Rect source;
};

class CRenderable
{
protected:
	SDL_Rect _Dest;
	SDL_Texture* _Texture;
	Frame* CurrentFrame;
public:
	SDL_Texture* GetTexture(){ return _Texture; }
	SDL_Rect* GetTextureSourceCoords(){ return &CurrentFrame->source; }
	SDL_Rect* GetTextureDestCoords(){ return &_Dest; }
	CRenderable(SDL_Texture* texture);
	~CRenderable(void);


	std::vector<Frame> Frames;
	void virtual OnFrame(){}
	void virtual Init(){}
};

