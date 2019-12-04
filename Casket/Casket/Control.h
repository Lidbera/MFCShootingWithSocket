#include "Sound.h"
#include "Scene.h"
#include "Lobby.h"
#include "Select.h"
#include "Multi.h"
#include "Match.h"
#include "Ingame.h"
#include "Data.h"

#pragma once
class Control
{
public:
	Player me, you;
	Sound *sound;
	SCENE scene;
	Scene *game;
	SOCKETFORCONTROL socket;
	bool server;
	char* serverIP;

public:
	Control();
	Control(Sound* sound);
	void Initialize(Sound* sound);

public:
	void Draw(CDC* pDC, int wx, int wy);
	void TimerCall(TIMER timer);
	void Finish();
	void KeyInput(bool b, KEY key);
	void KeyInput(WPARAM wParam);
	void MouseClick(CPoint point);

//Save 관련 - 입출력으로 저장 클래스를 만드는게 좋을까?
public:
	CHARACTER character;

//Socket 관련
public:
	bool sendData, once;
	void ServerDisconnect();
	Data GetData();
	void RecvData(Data data);
};

