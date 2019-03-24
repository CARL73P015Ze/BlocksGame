#pragma once

#include "stdafx.h"
#include "Renderable.h"
#include <SDL.h>
#include <string>
#include "map"
#include <vector>
#include "TextureLists.h"
struct FontSettings{
	int width;
	int height;
	int font_offset_x;
	int font_offset_y;
	std::string textureFileName;
};


class CRenderer: public CTextureList
{
private:
	SDL_Renderer* _Renderer;
	FontSettings _DefaultFontSettings;
	SDL_Texture* _DefaultFontTexture;
	char* _data_path;
	SDL_Rect _Source;
	SDL_Rect _Dest;



	void RenderChar(char& c, int x, int y, FontSettings* settings, SDL_Texture* font){
		_Source.w = settings->width; // 10
		_Source.h = settings->height; // 16
		_Source.x = ((c-32) % 28) * settings->width;
		_Source.y = ((c-32) / 28) * settings->height;

		_Source.x += settings->font_offset_x;
		_Source.y += settings->font_offset_y;

		_Dest.w = _Source.w;
		_Dest.h = _Source.h;
		_Dest.x = x;
		_Dest.y = y;

		SDL_RenderCopy(_Renderer, font, &_Source, &_Dest);
	}

	void RenderString(const std::string* str, int x, int y, FontSettings* settings, SDL_Texture* font){
		for(int i=0; i < str->size(); i++){
			char c = str->at(i);
			if(c <= '~' && c >= ' '){
				RenderChar(c, x, y, settings, font);
			}
			x += settings->width;
		}
	}

public:
	CRenderer(SDL_Renderer *renderer, FontSettings settings, char* data_path);
	~CRenderer(void);

	std::map<std::string, SDL_Texture*> _Textures;
	const int GetFontHeight(){ return _DefaultFontSettings.height; }
	SDL_Texture* GetTexture(std::string file){
		if(_Textures.count(file) > 0){
			return _Textures.at(file);
		}else{
			SDL_Texture* out = TryLoadImage(file);
			_Textures[file] = out;
			return out;
		}
	}

	void RemoveTexture(std::string file){
		SDL_DestroyTexture(_Textures.at(file));
	}

	// this is in the wrong place i think
	SDL_Texture* TryLoadImage(std::string file){
		SDL_Surface *bmp = nullptr;

		std::string temp = _data_path;
		//temp.append("\\resources\\");
		temp.append(file);
		bmp = SDL_LoadBMP(temp.c_str());
		if (bmp == nullptr){
			printf("%s", SDL_GetError());
			return nullptr;
		}
		SDL_Texture* out = SDL_CreateTextureFromSurface(_Renderer, bmp);
		SDL_FreeSurface(bmp);
		return out;
	}
	
	void Clear(){
		SDL_RenderClear(_Renderer);
	}

	void RenderString(const std::string* str, int x, int y){
		RenderString(str, x, y, &_DefaultFontSettings, _DefaultFontTexture);
	}

	void Render(SDL_Texture* texture, SDL_Rect* source, SDL_Rect* dest){
		SDL_RenderCopy(_Renderer, texture, source, dest);
	}

	void Render(std::vector<CRenderable*> renderableList){
		SDL_Rect* source;
		SDL_Rect* dest;
		SDL_Texture* texture;
		CRenderable* item;
		for(std::vector<CRenderable*>::iterator it = renderableList.begin(); 
							it != renderableList.end(); ++it){
			item = (*it);
			item->OnFrame();
			texture = item->GetTexture();
			source = item->GetTextureSourceCoords();
			dest = item->GetTextureDestCoords();
			SDL_RenderCopy(_Renderer, texture, source, dest);
		}
	}

};

