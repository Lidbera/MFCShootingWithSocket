#include "Data.h"
#include "Need.h"
#include "Resource.h"

#pragma once
class MovingObject
{
public:
	bool alive, move, draw, wait;
	char moveSpeed;
	Coord pos;
	short hp, ahp;
protected:
	char leftCenterRight;
	bool isPlayer, twink;
	short wait5;
	Player *player;
	int wx, wy, bmpID, waitDelay;
	BITMAP bitmap;
public:
	//boss
	short dieCount;
	bool die;

public:
	MovingObject();
	MovingObject(Player *p2);
	MovingObject(Player *player, KEY leftCenterRight);
	MovingObject(int _bmpID, Coord _pos, int _health);
	void CharSet();
	void Initial(bool allNew);
	void Move(char _x, char _y);
	void Destroy();
	void Draw(CDC* pDC, CDC* memDC);
	void WindowPos(int wx, int wy);
	void BeforeReady();
	void Ready();
	void SetBmpID(int bmpID);
	int GetBmpID();
};