#include "Scene.h"
#include "Sound.h"


#pragma once
class Select : public Scene
{
public:
	Select();
	Select(Sound* sound);

private:
	void Initialize();
	Rect character, left, right;
	Rect single, multi, back;
	Rect v_singleCheck, v_singleCheck_ok, v_singleCheck_cancel;

public:
	virtual void Draw(CDC* pDC, int wx, int wy) override;
	virtual void TimerCall(TIMER timer) override;
	virtual void Finish() override;
	virtual void MouseClick(CPoint point) override;
};

