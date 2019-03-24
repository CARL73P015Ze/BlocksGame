#include "StdAfx.h"
#include "Renderer.h"


CRenderer::CRenderer(SDL_Renderer *renderer, FontSettings settings, char* data_path)
{	
	_data_path = data_path;
	_Renderer = renderer;
	_DefaultFontSettings = settings;
	_DefaultFontTexture = GetTexture(settings.textureFileName);
}


CRenderer::~CRenderer(void)
{

    SDL_DestroyRenderer(_Renderer);
}
