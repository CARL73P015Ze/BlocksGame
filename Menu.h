#pragma once
#include "Component.h"
#include <vector>

#include "Renderer.h"

class CMenuItem{
public:
	std::string text;
	int id;
};

class CMenu : public CComponent{
private:
	std::vector<CMenuItem*> items;

	unsigned int selected;
	int _X;
	int _Y;
public:
	bool visible;
	CMenu();
	void SetX(int x);
	void SetY(int y);
	void Add(std::string text, int id);
	void Render(CRenderer* renderer);
	void SelectFirst();


	void HandleEvent(const ExternalEvent& e);
public:
	int selected_id;
};
