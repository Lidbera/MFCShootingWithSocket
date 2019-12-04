#include "pch.h"
#include "Ingame.h"

Ingame::Ingame() : Scene()
{
}

Ingame::Ingame(Sound* sound, Player* _me)
{
	me = _me;
	you = nullptr;
	multi = false;
	Initialize(true);
}

Ingame::Ingame(Sound* sound, Player *_me, Player *_you, bool _server) : Scene(sound)
{
	me = _me;
	you = _you;
	multi = true;
	server = _server;
	Initialize(false);
}

void Ingame::DataSet()
{
	if (server) {
		//넘김
		dfc.bossBmpID = boss.GetBmpID();
		dfc.pos = boss.pos;
		dfc.bossahp = boss.ahp;
		dfc.bosshp = boss.hp;
	}
	else {
		if (dfc.bossBmpID != -1) {
			//받음
			boss.hp = dfc.bosshp;
			boss.ahp = dfc.bossahp;
			boss.SetBmpID(dfc.bossBmpID);
			boss.pos = dfc.pos;
		}
	}

	if (you->shot) {
		CreateBullet();
	}
	if (dfc.shot) {
		BossBullet(1);
	}
	if (dfc.shot2) {
		BossBullet(2);
	}
	if (dfc.shot3) {
		BossBullet(3);
	}
	if (dfc.shot4) {
		BossBullet(4);
	}
}

void Ingame::Initialize(bool single)
{
	movedelay = 1000;
	if (single) {
		p1 = MovingObject(me, LECT_DOWN);
	}
	else {
		if (server) {
			p1 = MovingObject(me, LECT_LEFT);
		}
		else {
			p1 = MovingObject(me, LECT_RIGHT);
		}
		p2 = MovingObject(you);
	}
	stage = Stage(me);
	for (int i = 0; i < 30; i++) {
		pfire[i] = Bullet();
	}
	for (int i = 0; i < 50; i++) {
		efire[i] = Bullet();
	}
	if (server) {
		boss = MovingObject(IDB_BOSS, Coord(), 200);
	}
	else {
		boss = MovingObject(IDB_BOSS, Coord(), 200);
	}
	dfc = DataForClient();
}

void Ingame::Draw(CDC* pDC, int wx, int wy)
{
	StageCheck(wx, wy);
	if (multi) {
		DataSet();
	}
	BossPattern();

	CDC memDC;
	memDC.CreateCompatibleDC(pDC);

	//OBJ
	if (me->life > 0) {
		p1.Draw(pDC, &memDC);
		LifeDraw(1, pDC, &memDC, wx, wy);
	}
	if (multi) {
		if (you->life > 0) {
			p2.Draw(pDC, &memDC);
			LifeDraw(2, pDC, &memDC, wx, wy);
		}
	}
	for (int i = 0; i < pfc; i++) {
		pfire[i].Draw(pDC, &memDC, wx, wy);
	}
	for (int i = 0; i < efc; i++) {
		efire[i].Draw(pDC, &memDC, wx, wy);
	}
	//BOSS
	if (!boss.die) {
		boss.Draw(pDC, &memDC);
		BossHealth(pDC, &memDC, wx, wy);
	}
	else {
		if (me->life > 0) {
			//Rect rec = Rect(wx / 2 - 150, wy / 2 - 200, wx / 2 + 150, wy / 2 + 100);
			ui = Rect(100, 300, wx - 100, wy - 300);
			DrawRectImage(pDC, &memDC, IDB_PANEL, ui);
			DrawRectText(pDC, &memDC, L"승리", 50, ui);

			ok = Rect(ui.l + 20, ui.b - 100, ui.r - 20, ui.b - 20);
			DrawRectImage(pDC, &memDC, IDB_BTN, ok);
			DrawRectText(pDC, &memDC, L"확인", 20, ok);
		}
	}
	if (me->life <= 0) {
		ui = Rect(100, 300, wx - 100, wy - 300);
		DrawRectImage(pDC, &memDC, IDB_PANEL, ui);
		DrawRectText(pDC, &memDC, L"패배", 50, ui);

		ok = Rect(ui.l + 20, ui.b - 100, ui.r - 20, ui.b - 20);
		DrawRectImage(pDC, &memDC, IDB_BTN, ok);
		DrawRectText(pDC, &memDC, L"확인", 20, ok);
	}
	
	//UI
	UpdateFPS(pDC, &memDC, wx, wy);

	memDC.DeleteDC();
}

void Ingame::TimerCall(TIMER _timer)
{
}

void Ingame::Finish()
{
	//게임 종료시
	gameStart = false;
	socketBreak = true;
	gotoScene = LECT_LOBBY;
}

void Ingame::KeyInput(bool b, KEY key)
{
	if (me->life <= 0) {
		return;
	}

	switch (key) {
	case LECT_UP:
		p1.Move(0, -1 * p1.moveSpeed);
		break;
	case LECT_DOWN:
		p1.Move(0, 1 * p1.moveSpeed);
		break;
	case LECT_LEFT:
		p1.Move(-1 * p1.moveSpeed, 0);
		break;
	case LECT_RIGHT:
		p1.Move(1 * p1.moveSpeed, 0);
		break;
	case LECT_SPACE:
		if (p1.wait) {
			return;
		}
		if (shotDelay <= 0) {
			CreateBullet(*me);
			shotDelay = 5;
		}
		break;
	}
}

void Ingame::MouseClick(CPoint point)
{
	if ((boss.die && me->life > 0) || me->life <= 0) {
		if (ButtonClick(point, ok)) {
			gotoScene = LECT_LOBBY;
			socketBreak = true;
			socketError = false;
		}
	}
}

void Ingame::UpdateFPS(CDC* pDC, CDC* memDC, int wx, int wy)
{
	static float frameCount = 0.0f;
	static float timeElapsed = 0.0f;
	static int LastTime = (int)GetTickCount64();

	int curTime = (int)GetTickCount64();
	float timeDelta = (curTime - LastTime) * 0.001f;

	timeElapsed += timeDelta;
	frameCount++;

	CString str;
	static float fps = 0;
	CFont font, * pOldFont;
	font.CreatePointFont(100, L"맑은 고딕");
	pOldFont = (CFont*)memDC->SelectObject(&font);
	pDC->SetTextColor(RGB(0, 0, 0));
	pDC->SetTextAlign(TA_CENTER);

	fps = (float)frameCount / timeElapsed;

	if (timeElapsed >= 1.0f) {
		frameCount = 0;
		timeElapsed = 0.0f;
	}
	pDC->SetBkMode(TRANSPARENT);
	pDC->SelectObject(&font);
	str.Format(L"FPS: %.1f", fps);
	pDC->TextOutW(wx / 2, 15, str);

	pDC->SelectObject(*pOldFont);

	LastTime = curTime;
}

void Ingame::StageCheck(int wx, int wy)
{
	if (play) {
		if (shotDelay > 0) {
			shotDelay--;
		}
		HitCheck();
		stage.TimeSpan(wx, wy);
		if (stage.playerCome == 1) {
			p1.Ready();
			stage.playerCome = 2;
			stage.playerDie = 0;
		}
		else if (stage.playerDie == 2) {
			stage.playerCome = 0;
		}
		else if (stage.playerDie == 0) {
			stage.comeonce = true;
		}
	}
	else {
		play = true;
		p1.WindowPos(wx, wy);
		p1.BeforeReady();
		boss.pos = Coord(wx / 2 - 150, 50);
	}
	if (multi) {
		p2.pos = you->pos;
	}
}

void Ingame::HitCheck()
{
	RECT pRect, bRect, tRect;
	//플레이어
	if (!p1.wait) {
		if (me->life > 0) {
			pRect = { me->pos.x, me->pos.y, me->pos.x + 34, me->pos.y + 40 };
			for (int i = 0; i < efc; i++) {
				bRect = { efire[i].pos.x + 5, efire[i].pos.y + 5, efire[i].pos.x + efire[i].width - 5, efire[i].pos.y + efire[i].height - 5};
				if (IntersectRect(&tRect, &pRect, &bRect) != 0) {
					efire[i].Remove();
					p1.Destroy();
					stage.playerDie = 1;
				}
			}
		}
	}
	//보스
	if (boss.die) return;
	pRect = { boss.pos.x, boss.pos.y, boss.pos.x + 256, boss.pos.y + 158 };
	for (int i = 0; i < pfc; i++) {
		bRect = { pfire[i].pos.x, pfire[i].pos.y, pfire[i].pos.x + pfire[i].width, pfire[i].pos.y + pfire[i].height};
		if (IntersectRect(&tRect, &pRect, &bRect) != 0) {
			pfire[i].Remove();
			if (multi && server) {
				boss.Destroy();
			}
			else {
				boss.Destroy();
			}
		}
	}
}

void Ingame::BossHealth(CDC* pDC, CDC* memDC, int wx, int wy)
{
	BITMAP bitmap;
	CBitmap cBitmap;

	cBitmap.LoadBitmapW(IDB_HP);
	cBitmap.GetBitmap(&bitmap);
	memDC->SelectObject(cBitmap);
	DeleteObject(cBitmap);

	BLENDFUNCTION bf;
	bf.BlendOp = AC_SRC_OVER; 
	bf.BlendFlags = 0;
	bf.SourceConstantAlpha = 150; //0:투명 ~ 255:불투명
	bf.AlphaFormat = 0;

	int min = 10; 
	int max = wx - 20;
	per = (float)boss.hp / (float)boss.ahp;
	float res = (float)max * per;
	pDC->AlphaBlend(min, 10, (int)res, 40, memDC, 0, 0, bitmap.bmWidth, bitmap.bmHeight, bf);
}

void Ingame::CreateBullet(Player player)
{
	int num = -1;
	for (int i = 0; i < pfc; i++) {
		if (pfire[i].bmpID == 0) {
			num = i;
			break;
		}
	}
	if (num == -1) {
		return;
	}
	else {
		Coord c = player.pos + Coord(10, 0);
		pfire[num].Set(LECT_P1BULLET, c, Coord(0, -1));
		if (multi) {
			me->shot = true;
		}
	}
}

void Ingame::CreateBullet()
{
	//for client
	int num = -1;
	for (int i = 0; i < pfc; i++) {
		if (pfire[i].bmpID == 0) {
			num = i;
			break;
		}
	}
	if (num == -1) {
		return;
	}
	else {
		Coord c = you->pos + Coord(10, 0);
		pfire[num].Set(LECT_P1BULLET, c, Coord(0, -1));
	}
}

void Ingame::CreateBullet(int bmpID, short speed, Coord dir)
{
	int num = -1;
	for (int i = 0; i < efc; i++) {
		if (efire[i].bmpID == 0) {
			num = i;
			break;
		}
	}
	if (num == -1) {
		return;
	}
	else {
		Coord c = boss.pos + Coord(100, 0);
		efire[num].Set(bmpID, speed, c, dir);
	}
}

void Ingame::BossBullet(char num)
{
	switch (num) {
	case 1:
		CreateBullet(IDB_BBUL, 2, Coord(1, 0));
		CreateBullet(IDB_BBUL, 2, Coord(-1, 0));
		CreateBullet(IDB_BBUL, 2, Coord(0, 1));
		CreateBullet(IDB_BBUL, 2, Coord(0, -1));
		break;
	case 2:
		CreateBullet(IDB_BBUL, 2, Coord(1, 1));
		CreateBullet(IDB_BBUL, 2, Coord(-1, -1));
		CreateBullet(IDB_BBUL, 2, Coord(1, -1));
		CreateBullet(IDB_BBUL, 2, Coord(-1, 1));
		break;
	case 3:
		CreateBullet(IDB_BBUL, 4, Coord(0, 1));
		CreateBullet(IDB_BBUL, 4, Coord(-1, 1));
		CreateBullet(IDB_BBUL, 4, Coord(1, 1));
		break;
	case 4:
		if (shot4start) {
			if (shot4num < 7) {
				shot4num++;
			}
			else {
				shot4num = 0;
			}
		}
		else {
			shot4start = true;
			shot4num = 0;
		}
		Coord dir = Coord();
		switch (shot4num) {
		case 0:
			dir = Coord(-1, 1);
			break;
		case 1:
			dir = Coord(0, 1);
			break;
		case 2:
			dir = Coord(1, 1);
			break;
		case 3:
			dir = Coord(1, 0);
			break;
		case 4:
			dir = Coord(1, -1);
			break;
		case 5:
			dir = Coord(0, -1);
			break;
		case 6:
			dir = Coord(-1, -1);
			break;
		case 7:
			dir = Coord(-1, 0);
			break;
		}
		CreateBullet(IDB_BBUL, 1, dir);
		break;
	}
}

void Ingame::BossPattern()
{
	if (boss.GetBmpID() == 0) {
		return;
	}

	if (multi && !server) {
		return;
	}

	movedelay++;
	if (movedelay > 50) {
		srand((unsigned int)time(0));
		ranx = rand() % 476 + 10;
		rany = rand() % 476 + 10;
		movedelay = 0;
	}

	if (boss.pos.x < ranx && boss.pos.x < 486) {
		boss.pos.x += 1;
	}
	else if (boss.pos.x > ranx&& boss.pos.x > 0) {
		boss.pos.x -= 1;
	}
	if (boss.pos.y < rany && boss.pos.y < 486) {
		boss.pos.y += 1;
	}
	else if (boss.pos.y > rany&& boss.pos.y > 0) {
		boss.pos.y -= 1;
	}

	if (per > 0.8) {
		flowdelay++;
		if (flowdelay > 30) {
			flowdelay = 0;

			dfc.shot3 = true;
			BossBullet(3);
		}
	}
	else if (per > 0.45 && per <= 0.8) {
		flowdelay++;
		if (flowdelay == 30) {
			dfc.shot = true;
			BossBullet(1);
		}
		else if (flowdelay >= 60) {
			dfc.shot2 = true;
			BossBullet(2);
			flowdelay = 0;
		}
	}
	else if (per <= 0.45) {
		flowdelay++;
		if (flowdelay > 6) {
			flowdelay = 0;

			dfc.shot4 = true;
			BossBullet(4);
		}
	}
}

void Ingame::LifeDraw(int num, CDC* pDC, CDC* memDC, int wx, int wy)
{
	int x = 0, y = 0;
	if (multi) {
		if (server) {
			for (int i = 0; i < me->life; i++) {
				x = 10; y = 70 + 20 * i;
				DrawRectImage(pDC, memDC, IDB_LIFE, Rect(x, y, x + 16, y + 16), 0, 0, 255);
			}
			for (int i = 0; i < you->life; i++) {
				x = wx - 26; y = 70 + 20 * i;
				DrawRectImage(pDC, memDC, IDB_LIFE, Rect(x, y, x + 16, y + 16), 0, 0, 255);
			}
		}
		else {
			for (int i = 0; i < you->life; i++) {
				x = 10; y = 70 + 20 * i;
				DrawRectImage(pDC, memDC, IDB_LIFE, Rect(x, y, x + 16, y + 16), 0, 0, 255);
			}
			for (int i = 0; i < me->life; i++) {
				x = wx - 26; y = 70 + 20 * i;
				DrawRectImage(pDC, memDC, IDB_LIFE, Rect(x, y, x + 16, y + 16), 0, 0, 255);
			}
		}
	}
	else {
		for (int i = 0; i < me->life; i++) {
			x = 10; y = 70 + 20 * i;
			DrawRectImage(pDC, memDC, IDB_LIFE, Rect(x, y, x + 16, y + 16), 0, 0, 255);
		}
	}
}
