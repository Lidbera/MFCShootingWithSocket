#include "pch.h"
#include "Match.h"

Match::Match() : Scene()
{
}

Match::Match(Sound* sound) : Scene(sound)
{
	once = false;
	socketError = false;
}

void Match::Initialize()
{
}

void Match::Draw(CDC* pDC, int wx, int wy)
{
	CDC memDC;
	memDC.CreateCompatibleDC(pDC);

	Rect ui = Rect(100, 300, wx - 100, wy - 300);
	DrawRectImage(pDC, &memDC, IDB_PANEL, ui);

	//���
	if (socketError) {
		cancel = Rect(ui.l + 20, ui.b - 100, ui.r - 20, ui.b - 20);
		DrawRectImage(pDC, &memDC, IDB_BTN, cancel);
		DrawRectText(pDC, &memDC, L"���", 20, cancel);
	}

	//IP
	CString str;
	if (server) {
		str.Format(L"����� IP: [%s]", CString(GetMyIP()));
	}
	else {
		str.Format(L"���� ���� IP: [%s]", CString(serverIP));
	}
	DrawRectText(pDC, &memDC, str, 20, Rect(ui.l, ui.t, ui.r, ui.t + 150));
	str.Format(L"�����ߡ�");
	DrawRectText(pDC, &memDC, str, 30, ui);
	if (server) {
		str.Format(L"��������� �ߴ°� �����Դϴ�."); 
		DrawRectText(pDC, &memDC, str, 15, Rect(ui.l, ui.t + 100, ui.r, ui.b + 100));;
		str.Format(L"(��Ȱ�� ��Ƽ�� ���� ������ �̻��)");
		DrawRectText(pDC, &memDC, str, 15, Rect(ui.l, ui.t + 130, ui.r, ui.b + 130));;
	}

	memDC.DeleteDC();

	if (!once) {
		once = true;
		//���� Ȥ�� Ŭ�� ���� ����
		matchLoaded = true;
	}
}

void Match::TimerCall(TIMER timer)
{
}

void Match::Finish()
{
}

void Match::MouseClick(CPoint point)
{
	if (ButtonClick(point, cancel)) {
		gotoScene = LECT_SELECT;
		socketBreak = true;
		socketError = false;
	}
}
