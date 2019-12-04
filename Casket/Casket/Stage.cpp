#include "pch.h"
#include "Stage.h"

Stage::Stage()
{
}

Stage::Stage(Player* _player)
{
	player = _player;
	playerCome = 0;
	playerDie = 0;
	dieonce = true;
	comeonce = true;
}

void Stage::TimeSpan(int _wx, int _wy)
{
	time++;
	wx = _wx;
	wy = _wy;

	if (playerCome == 0) {
		dieonce = true;
		PlayerCome();
	}
	else if (playerDie == 1) {
		PlayerDie();
	}
}

void Stage::PlayerCome()
{
	if (player->pos.y <= wy - 150) {
		if (comeonce) {
			playerCome = 1;
			comeonce = false;			
		}
	}
	else {
		player->pos.y -= 3;
	}
}

void Stage::PlayerDie()
{
	if (player->pos.y > wy + 50) {
		if (dieonce) {
			playerDie = 2;
			dieonce = false;
		}
	}
	else {
		player->pos.y += 10;
	}
}