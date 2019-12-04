#include "Scene.h"
#include "Sound.h"


#pragma once
class Match : public Scene
{
public:
	Match();
	Match(Sound* sound);

private:
	void Initialize();
	Rect ui, cancel;
	bool once;

public:
	virtual void Draw(CDC* pDC, int wx, int wy) override;
	virtual void TimerCall(TIMER _timer) override;
	virtual void Finish() override;
	virtual void MouseClick(CPoint _point) override;
};

