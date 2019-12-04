#include "Scene.h"
#include "Sound.h"


#pragma once
class Multi : public Scene
{
public:
	Multi();
	Multi(Sound* sound);

private:
	void Initialize();
	Rect rserver, rclient, back;
	Rect v_ipInput, v_ipInput_ok, v_ipInput_cancel, v_ipInputWindow;
	MULTISELECT select;
	bool input;
	short inputDelay, inputDelay2;
	void AppendEndToIP(char b);
	void RemoveEndToIP();

public:
	virtual void Draw(CDC* pDC, int wx, int wy) override;
	virtual void TimerCall(TIMER timer) override;
	virtual void Finish() override;
	virtual void KeyInput(WPARAM wParam) override;
	virtual void MouseClick(CPoint point) override;
};
