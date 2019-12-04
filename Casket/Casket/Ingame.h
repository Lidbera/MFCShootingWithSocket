#include "Scene.h"
#include "Sound.h"
#include "MovingObject.h"
#include "Stage.h"
#include "Bullet.h"

#define pfc 100
#define efc 100

#pragma once
class Ingame : public Scene
{
public:
	Ingame();
	Ingame(Sound* sound, Player* me);
	Ingame(Sound* sound, Player *me, Player *you, bool _server);
	void DataSet();

private:
	void Initialize(bool single);
	Stage stage;
	Player* me, * you;
	MovingObject p1, p2, boss;
	Bullet pfire[pfc], efire[efc];
	bool multi, play, shot4start, pattern;
	int shotDelay, shot4num, flowdelay, movedelay;
	int ranx, rany;
	float per;
	Rect ui, ok;
	void UpdateFPS(CDC* pDC, CDC* memDC, int wx, int wy);

private:
	void StageCheck(int wx, int wy);
	void HitCheck();
	void BossHealth(CDC* pDC, CDC* memDC, int wx, int wy);
	void CreateBullet(Player player);
	void CreateBullet();
	void CreateBullet(int bmpID, short speed, Coord dir);
	void BossBullet(char num);
	void BossPattern();
	void LifeDraw(int num, CDC* pDC, CDC* memDC, int wx, int wy);

public:
	virtual void Draw(CDC* pDC, int wx, int wy) override;
	virtual void TimerCall(TIMER _timer) override;
	virtual void Finish() override;
	virtual void KeyInput(bool b, KEY key) override;
	virtual void MouseClick(CPoint _point) override;
};

