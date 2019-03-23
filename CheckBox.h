#pragma once

class EventArgs{
};

class EventHandler{
public:
	void handle(EventArgs* args){
	}
};

class CCheckBox
{
private:
	bool _Checked;
	char* _Text;
	EventHandler handle;
public:
	bool isChecked(){return _Checked;}
	void Check(bool checked){_Checked = checked;}
	void setText(char* text){_Text = text;}
	void OnCheck() { handle.handle(new EventArgs()); }
	void Check(EventHandler handle){}
	CCheckBox(void);
	~CCheckBox(void);
};

