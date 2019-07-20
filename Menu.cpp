#include "StdAfx.h"
#include "Menu.h"



CMenu::CMenu(){
	selected = 0;
	selected_id = -1;
	visible = true;
	_X = 50;
	_Y = 50;
}

void CMenu::SetX(int x){_X = x;}
void CMenu::SetY(int y){_Y = y;}

void CMenu::HandleEvent(const ExternalEvent& e){
	
	if(e == E_DPAD_DOWN_PRESS){
		if(selected < items.size())
			selected++;
	}
	
	if( e == E_DPAD_UP_PRESS){
		if(selected > 0)
			selected--;
	}

	if( e == E_PRIMARY_BUTTON_DOWN){
		selected_id = items.at(selected)->id;
	}

}

void CMenu::Add(std::string text, int id){
	CMenuItem* item = new CMenuItem();
	item->text = text;
	item->id = id;
	items.push_back(item);
}

void CMenu::Render(CRenderer* renderer){
	if(!visible)
		return;
	std::string str;
	std::vector<CMenuItem*>::const_iterator it = items.begin();
	int offset = 0;
	unsigned int i = 0;
	while(it != items.end()){
		std::string val = (*it)->text;
		if(selected == i){
			val = ">" + val + "<";
			renderer->RenderString(&val, _X, _Y+offset);
		}else{
			renderer->RenderString(&val, _X, _Y+offset);
		}
		offset += renderer->GetFontHeight();
		it++;
		i++;
	}
}

void CMenu::SelectFirst(){
	selected = 0;
}