#include "Data.h"
#include "Need.h"
#include "resource.h"

#pragma once
class Bullet
{
private:
	BITMAP bitmap;
	short ranx, rany;

public:
	int bmpID, speed;
	Coord pos, dir;
	short width, height;
	bool once;

	Bullet();
	void Set(BULLET bullet, Coord pos, Coord dir);
	void Set(int bmpID, short spd, Coord pos, Coord dir);
	void Remove();
	void Draw(CDC* pDC, CDC* memDC, int wx, int wy);
};

