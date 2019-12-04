#include "pch.h"
#include "Game.h"


Game::Game()
	: Scene()
{
}

Game::Game(Sound* sound) : Scene(sound)
{
}

void Game::Draw(CDC* pDC, int wx, int wy)
{
	if (control == nullptr) {
		return;
	}

	control->Draw(pDC, wx, wy);
}

void Game::TimerCall(TIMER _timer)
{
	if (control == nullptr) {
		return;
	}

	control->TimerCall(_timer);
}

void Game::Finish()
{
	if (control == nullptr) {
		return;
	}

	control->Finish();

	delete control;
}

void Game::KeyInput(KEY _key)
{
	if (control == nullptr) {
		return;
	}

	control->KeyInput(_key);
}

void Game::MouseClick(CPoint _point)
{
	if (control == nullptr) {
		return;
	}

	control->MouseClick(_point);
}