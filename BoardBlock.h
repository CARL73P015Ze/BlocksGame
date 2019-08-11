#pragma once
#include "Block.h"
#include "Animation.h"
#include "Renderable.h"
#include <vector>

class AnimationFrame
{
public:
	SDL_Rect Source;
};

class AnimationKeyFrame{
public:
	SDL_Rect* GetSourceCoords(){return nullptr;}
	SDL_Rect RelativeCoords;/*
						->withTexture("C:/Users/room101/Desktop/Columns/psd/gems.bmp")
						->withSourceCoords()
						->withRelativeCoords()
						->withKeyTime(0);*/
	int tweenType;
};



class BoardBlock : CRenderable
{
private:
	Animation _Animation;
	Animation _AnimateRemoval;
	Animation* _CurrentAnimation;

	Block* _Block;


public:
	BoardBlock(CTextureList* textures, Block* block);
	~BoardBlock(void);
	void Init(){
		// preload the images, etc.
		_CurrentTexture = _TextureList->GetTexture("C:/Users/room101/Desktop/Columns/psd/gems.bmp");
		_CurrentAnimation = &_Animation;
		_CurrentAnimation->Start();
	}

	void OnFrame(){
		AnimationFrame* frame = _CurrentAnimation->GetCurrentFrame();
		if(_Block->remove && _CurrentAnimation != &_AnimateRemoval){
			_CurrentAnimation = &_AnimateRemoval;
			_CurrentAnimation->Start();
		}
		
		_CurrentAnimation->OnAnimate();
		_Source = &frame->Source;

		_Dest.x = 50;
		_Dest.y = 50;
		_Dest.w = _Source->w;
		_Dest.h = _Source->h;
	}
};