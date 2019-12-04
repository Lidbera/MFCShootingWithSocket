#include "Data.h"

#pragma once
class Stage
{
public:
	Stage();
	Stage(Player *player);
	void TimeSpan(int wx, int wy);
	bool comeonce;

private:
	int time, wx, wy;
	bool dieonce;
	Player* player;

//trigger
public:
	int playerCome, playerDie;
	
private:
	void PlayerCome();
	void PlayerDie();
};

