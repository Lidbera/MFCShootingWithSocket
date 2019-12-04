#include "pch.h"
#include "MovingObject.h"

MovingObject::MovingObject()
{
	Initial(true);
}

MovingObject::MovingObject(Player* p2)
{
	move = false;
	draw = true;
	player = p2;
	isPlayer = true;
	alive = true;
	waitDelay = 0;
	wait5 = 0;

	CharSet();
}

MovingObject::MovingObject(Player *_player, KEY _leftCenterRight)
{
	move = false;
	wait = false;
	draw = false;
	player = _player;
	isPlayer = true;
	alive = true;
	leftCenterRight = _leftCenterRight;
	waitDelay = 0;
	wait5 = 0;

	CharSet();
}

MovingObject::MovingObject(int _bmpID, Coord _pos, int _health)
{
	move = false;
	wait = false;
	draw = true;
	Initial(false);
	isPlayer = false;
	bmpID = _bmpID;
	pos = _pos;
	ahp = hp = _health;
	dieCount = 0;
	die = false;
	waitDelay = 0;
	wait5 = 0;
}

void MovingObject::CharSet()
{
	switch (player->bmpID) {
	case IDB_CHAR:
		//기본캐
		moveSpeed = 3;
		break;
	}
}

void MovingObject::Initial(bool allNew)
{
	alive = false;
	if (allNew) {
		moveSpeed = 0;
		pos = Coord();
	}
}

void MovingObject::Move(char _x, char _y)
{
	if (!move) return;

	if (isPlayer) {
		if (wx >= player->pos.x + bitmap.bmWidth + _x && 
			0 < player->pos.x + _x) {
			player->pos.x += _x;
		}
		if (wy >= player->pos.y + bitmap.bmHeight + _y &&
			0 < player->pos.y + _y) {
			player->pos.y += _y;
		}
	}
	else {
		pos = pos + Coord(_x, _y);
	}
}

void MovingObject::Destroy()
{
	if (isPlayer) {
		move = false;
		//플레이어 파괴 이펙트
		if (player->life - 1 > 0) {
			wait = true;
			waitDelay = 0;
			wait5 = 0;
			player->life--;
			dieCount = 1;
			while (move) {
				printf("wait");
				//다시 올라올때까지 대기
			}
			twink = true;
		}
		else {
			//플레이어 패배
			bmpID = 0;
			player->life = 0;
			dieCount = 1;
		}
	}
	else {
		if (hp > 0) {
			hp--;
			//보스 피격 이펙트
		}
		else {
			//보스 파괴 이펙트
			dieCount = 1;
		}
	}
}


void MovingObject::Draw(CDC* pDC, CDC *memDC)
{
	if (!draw) return;
	if (isPlayer) {
		if (player->bmpID == 0) return;
	}
	else {
		if (bmpID == 0) return;
	}

	CBitmap cBitmap;
	if (isPlayer) {
		cBitmap.LoadBitmapW(player->bmpID);
	}
	else {
		cBitmap.LoadBitmapW(bmpID);
	}
	cBitmap.GetBitmap(&bitmap);

	memDC->SelectObject(cBitmap);
	DeleteObject(cBitmap);

	if (isPlayer) {
		if (wait) {
			if (wait5 > 20) { //무적시간
				wait = false;
				twink = false;
				wait5 = 0;
			}
			if (waitDelay < 10) {
				waitDelay++;
			}
			else {
				wait5++;
				waitDelay = 0;
			}
		}
		if (twink) {
			if (waitDelay >= 5 && waitDelay < 10) {
				return;
			}
		}
		if (dieCount > 0) {
			CBitmap cBitmap2;
			BITMAP bitmap2;
			cBitmap2.LoadBitmapW(IDB_BOMB);
			cBitmap2.GetBitmap(&bitmap2);
			memDC->SelectObject(cBitmap2);
			DeleteObject(cBitmap2);
			pDC->TransparentBlt(player->pos.x - 120, player->pos.y - 120, bitmap2.bmWidth / 9, bitmap2.bmHeight, memDC,
				bitmap2.bmWidth / 9 * dieCount, 0, bitmap2.bmWidth / 9, bitmap2.bmHeight, RGB(0, 0, 255));
			if (dieCount < 10) {
				dieCount++;
			}
			else if (dieCount >= 10) {
				dieCount = 0;
			}
		}
		pDC->TransparentBlt(player->pos.x, player->pos.y, bitmap.bmWidth / 2, bitmap.bmHeight, memDC, 0, 0, bitmap.bmWidth / 2, bitmap.bmHeight, RGB(0, 0, 255));
	}
	else {
		//boss
		if (dieCount > 0) {
			CBitmap cBitmap2;
			BITMAP bitmap2;
			cBitmap2.LoadBitmapW(IDB_BOMB);
			cBitmap2.GetBitmap(&bitmap2);
			memDC->SelectObject(cBitmap2);
			DeleteObject(cBitmap2);
			pDC->TransparentBlt(pos.x, pos.y, bitmap2.bmWidth / 9, bitmap2.bmHeight, memDC,
				bitmap2.bmWidth / 9 * dieCount, 0, bitmap2.bmWidth / 9, bitmap2.bmHeight, RGB(0, 0, 255));
			if (dieCount < 10) {
				dieCount++;
			}
			else if (dieCount >= 10) {
				dieCount = 0;
				bmpID = 0;
				die = true;
				//보스 죽음
			}
		}
		pDC->TransparentBlt(pos.x, pos.y, bitmap.bmWidth, bitmap.bmHeight, memDC, 0, 0, bitmap.bmWidth, bitmap.bmHeight, RGB(0, 0, 255));
	}
}

void MovingObject::WindowPos(int _wx, int _wy)
{
	wx = _wx;
	wy = _wy;
}

void MovingObject::BeforeReady()
{
	draw = true;
	if (leftCenterRight == LECT_LEFT) {
		//좌측
		player->pos = Coord(wx / 2 - 100, wy + 50);
	}
	else if (leftCenterRight == LECT_DOWN) {
		//중앙
		player->pos = Coord(wx / 2, wy + 50);
	}
	else if (leftCenterRight == LECT_RIGHT) {
		//우측
		player->pos = Coord(wx / 2 + 100, wy + 50);
	}
}

void MovingObject::Ready()
{
	move = true;
}

void MovingObject::SetBmpID(int _bmpID)
{
	bmpID = _bmpID;
}

int MovingObject::GetBmpID()
{
	return bmpID;
}
