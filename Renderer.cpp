#include "StdAfx.h"
#include "Renderer.h"


CRenderer::CRenderer(SDL_Renderer *renderer, FontSettings settings)
{	
	_Renderer = renderer;
	_DefaultFontSettings = settings;
	_DefaultFontTexture = GetTexture(settings.textureFileName);
}


CRenderer::~CRenderer(void)
{

    SDL_DestroyRenderer(_Renderer);
}
