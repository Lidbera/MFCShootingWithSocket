#include "Sound.h"
#include "Need.h"
#include "resource.h"
#include "Data.h"

#pragma once
class Scene
{
protected:
	Sound* sound;

public:
	VIEW view;
	SCENE gotoScene;
	CHARSELECT charSelect;
	bool server;
	char serverIP[15];
	bool matchLoaded, socketBreak, socketError;
	bool gameStart;
	DataForClient dfc;

public:
	Scene();
	Scene(Sound* sound);

private:
	void Initialize();

public:
	virtual void Draw(CDC* pDC, int wx, int wy);
	virtual void TimerCall(TIMER timer);
	virtual void Finish();
	virtual void KeyInput(bool b, KEY key);
	virtual void KeyInput(WPARAM wParam);
	virtual void MouseClick(CPoint point);

public:
	bool ButtonClick(CPoint point, Rect rect);
	void DrawRectImage(CDC* pDC, CDC* memDC, int bmpID, Rect rect);
	void DrawRectImage(CDC* pDC, CDC* memDC, int bmpID, Rect rect, int r, int g, int b);
	void DrawRectText(CDC* pDC, CDC* memDC, CString str, int fontSize, Rect rect);
	char* GetMyIP();
};
