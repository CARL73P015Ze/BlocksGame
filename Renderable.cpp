#include "StdAfx.h"
#include "Renderable.h"


CRenderable::CRenderable(SDL_Texture* texture)
{
	_Texture = texture;
}


CRenderable::~CRenderable(void)
{
}
		