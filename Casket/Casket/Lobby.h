#include "Scene.h"
#include "Sound.h"


#pragma once
class Lobby : public Scene
{
public:
	Lobby();
	Lobby(Sound* sound);

private:
	void Initialize();
	Rect background, charInfo, option, play;
	Rect v_charInfo, v_charInfo_ok;
	Rect v_option, v_option_ok;

public:
	virtual void Draw(CDC* pDC, int wx, int wy) override;
	virtual void TimerCall(TIMER timer) override;
	virtual void Finish() override;
	virtual void MouseClick(CPoint point) override;
};

