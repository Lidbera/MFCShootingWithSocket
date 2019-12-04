#include "Scene.h"
#include "Control.h"

#pragma once
class Game : public Scene
{
private:
	Control *control;

public:
	Game();
	Game(Sound *sound);

public:
	virtual void Draw(CDC* pDC, int wx, int wy) override;
	virtual void TimerCall(TIMER _timer) override;
	virtual void Finish() override;
	virtual void KeyInput(KEY _key) override;
	virtual void MouseClick(CPoint _point) override;
};