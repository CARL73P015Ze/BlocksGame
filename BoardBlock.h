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


class Animation
{
public:
	std::vector<AnimationKeyFrame*> frames; // must always have one
	AnimationFrame CurrentFrame;
	void Start(){}
	AnimationFrame* GetCurrentFrame(){return &CurrentFrame;}
	void OnAnimate(){
	/*	_CurrentAnimation->MaxFrames = 3;
		_CurrentAnimation->SetFrameRate(1);
		_CurrentAnimation->Oscillate = true;*/
		
	//	_Source.y = _CurrentAnimation->GetCurrentFrame() * 64;
	//	RelativeCoords = frames[1]->RelativeCoords - frames[2]->RelativeCoords;
	}
	SDL_Rect RelativeCoords;
};



/*
class AnimationFrameBuilder{
public:
	AnimationFrameBuilder* withSourceCoords(){return this;}
	AnimationFrameBuilder* withKeyTime(short ticks){return this;}
	AnimationFrameBuilder* withTexture(std::string texture){return this;}
	AnimationFrame* build(){return new AnimationFrame();}

	
	AnimationFrameBuilder* withMovement(int x, int y){return this;}
	
	AnimationFrameBuilder* withLinearTween(short ticks){return this;}
		//this.time, this.begin, this.change, this.duration
	int linearTween (int time, int begin, int change, int duration) {
		return change*time/duration + begin;
	};

	int QuadTween (int time, int begin, int change, int duration) {
		return change*(time/=duration)*time + begin;
	};

	int CubicTween (int time, int begin, int change, int duration) {
		return 0;//change * Math.pow (time/duration, 3) + begin;
	};

	int pulse(int time, int begin, int change, int duration){
		// use sin curve for calulating a smooth pulse
	}
};
*/

/*
class AnimationFactory{
public:
	// at some point make this load the animation from a config file, rather than hard code it..
	Animation GetBlockAnimation(){
		Animation anim;
		
		AnimationFrameBuilder* b;
		anim.frames.push_back(b
						->withTexture("C:/Users/room101/Desktop/Columns/psd/gems.bmp")
						->withSourceCoords()
						->withKeyTime(0)
						->build());
		frames.push_back(b->withSourceCoords()->withKeyTime(30)->build());
		frames.push_back(b->withSourceCoords()->withKeyTime(60)->build());
		frames.push_back(b->withSourceCoords()->withKeyTime(90)->build());
		frames.push_back(b->withSourceCoords()->withKeyTime(120)->build());
		anim.loop = false;
		anim.Start();
	}

}*/

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