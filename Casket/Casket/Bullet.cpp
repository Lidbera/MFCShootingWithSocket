#include "pch.h"
#include "Bullet.h"
#include <cstdlib>

Bullet::Bullet() {
	width = 0;
	height = 0;
	once = false;
	bmpID = 0;
}
void Bullet::Set(BULLET bullet, Coord _pos, Coord _dir)
{
	//보스는 그냥 편하게 원으로 ㄱ
	switch (bullet) {
	case LECT_P1BULLET:
		bmpID = IDB_BUL;
		Set(bmpID, 4, _pos, _dir);
		break;
	case LECT_B1BULLET:
		bmpID = IDB_BBUL;
		Set(bmpID, 1, _pos, _dir);
		break;
	}
}
void Bullet::Set(int _bmpID, short spd, Coord _pos, Coord _dir)
{
	//보스는 그냥 편하게 원으로 ㄱ
	bmpID = _bmpID;
	srand((unsigned int)time(0));
	ranx = rand() % 3 + 1;
	rany = rand() % 2 + 1;
	speed = spd;
	pos = _pos;
	dir = _dir;
}

void Bullet::Remove()
{
	width = 0;
	height = 0;
	once = false;
	bmpID = 0;
}

void Bullet::Draw(CDC* pDC, CDC* memDC, int wx, int wy)
{
	if (bmpID == 0) return;
	if (pos.y <= 0 || pos.y >= wy || pos.x <= 0 || pos.x >= wx) {
		Remove();
	}

	pos.x += dir.x * speed;
	pos.y += dir.y * speed;

	CBitmap cBitmap;
	cBitmap.LoadBitmapW(bmpID);
	cBitmap.GetBitmap(&bitmap);

	memDC->SelectObject(cBitmap);
	DeleteObject(cBitmap);

	if (!once) {
		once = true;
		width = bitmap.bmWidth;
		height = bitmap.bmHeight;
	}

	if (bmpID == 0) return;
	pDC->TransparentBlt(pos.x, pos.y, bitmap.bmWidth, bitmap.bmHeight, memDC, 0, 0, bitmap.bmWidth, bitmap.bmHeight, RGB(0, 0, 255));
}