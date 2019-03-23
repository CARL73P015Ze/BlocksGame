#include "StdAfx.h"
#include "Menu.h"



CMenu::CMenu(){
	selected = 0;
	visible = true;
	_X = 50;
	_Y = 50;
}

void CMenu::SetX(int x){_X = x;}
void CMenu::SetY(int y){_Y = y;}

void CMenu::HandleEvent(const ExternalEvent& e){
	if(selected > 0){
		if(e == E_DPAD_DOWN_PRESS){
			if(selected < items.size())
				selected ++;
		}
		if( e == E_DPAD_UP_PRESS){
			if(selected > 1)
				selected --;
		}

		if( e == E_PRIMARY_BUTTON_UP){
			items.at(--selected)->OnClick->OnEvent();
		}
	}
}

void CMenu::Add(std::string text, CEvent* OnClick){
	CMenuItem* item = new CMenuItem();
	item->text = text;
	item->OnClick = OnClick;
	items.push_back(item);
}

void CMenu::Render(CRenderer* renderer){
	if(!visible)
		return;
	std::string str;
	std::vector<CMenuItem*>::const_iterator it = items.begin();
	int offset = 0;
	int i = 1;
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
	selected = 1;
}