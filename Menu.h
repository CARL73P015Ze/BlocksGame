#pragma once
#include "Component.h"
#include <vector>

#include "Renderer.h"

class CMenuItem{
public:
	std::string text;
	CEvent* OnClick;
};

class CMenu : public CComponent{
private:
	std::vector<CMenuItem*> items;

	 	int selected;
		int _X;
		int _Y;
public:
	bool visible;
	CMenu();
	void SetX(int x);
	void SetY(int y);
	void Add(std::string text, CEvent* OnClick);
	void Render(CRenderer* renderer);
	void SelectFirst();


	void HandleEvent(const ExternalEvent& e);

};
