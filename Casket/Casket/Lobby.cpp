#include "pch.h"
#include "Lobby.h"

Lobby::Lobby() : Scene()
{
}

Lobby::Lobby(Sound* sound) : Scene(sound)
{
}

void Lobby::Initialize()
{
}

void Lobby::Draw(CDC* pDC, int wx, int wy)
{
	CDC memDC;
	memDC.CreateCompatibleDC(pDC);

	//BACKGROUND
	background = Rect(0, 0, wx, wy);
	DrawRectImage(pDC, &memDC, 0, background); //배경으로 바꿔야

	//CHARINFO
	charInfo = Rect(15, 15, 315, 115);
	DrawRectImage(pDC, &memDC, IDB_BTN, charInfo);
	DrawRectText(pDC, &memDC, L"플레이어 정보", 15, charInfo);

	//OPTION
	option = Rect(wx - 115, 15, wx - 15, 115);
	DrawRectImage(pDC, &memDC, IDB_BTN, option);
	DrawRectText(pDC, &memDC, L"설정", 15, option);

	//PLAY
	play = Rect(15, wy - 130, wx - 15, wy - 10);
	DrawRectImage(pDC, &memDC, IDB_BTN, play);
	DrawRectText(pDC, &memDC, L"시작", 20, play);

	switch (view) {
	case LECT_CHARINFO:
		v_charInfo = Rect(100, 200, wx - 100, wy - 200);
		DrawRectImage(pDC, &memDC, IDB_PANEL, v_charInfo);
		DrawRectText(pDC, &memDC, L"플레이어 정보", 20, v_charInfo);
		//확인
		v_charInfo_ok = Rect(v_charInfo.l + 30, v_charInfo.b - 120, v_charInfo.r - 30, v_charInfo.b - 30);
		DrawRectImage(pDC, &memDC, IDB_BTN, v_charInfo_ok);
		DrawRectText(pDC, &memDC, L"확인", 20, v_charInfo_ok);
		break;
	case LECT_OPTION:
		v_option = Rect(100, 200, wx - 100, wy - 200);
		DrawRectImage(pDC, &memDC, IDB_PANEL, v_option);
		DrawRectText(pDC, &memDC, L"설정", 20, v_option);
		//확인
		v_option_ok = Rect(v_option.l + 30, v_option.b - 120, v_option.r - 30, v_option.b - 30);
		DrawRectImage(pDC, &memDC, IDB_BTN, v_option_ok);
		DrawRectText(pDC, &memDC, L"확인", 20, v_option_ok);
		break;
	}

	memDC.DeleteDC();
}

void Lobby::TimerCall(TIMER _timer)
{
}

void Lobby::Finish()
{
}

void Lobby::MouseClick(CPoint point)
{
	switch (view) {
	case LECT_CHARINFO:
		if (ButtonClick(point, v_charInfo)) {
			//플레이어 정보 뷰
			if (ButtonClick(point, v_charInfo_ok)) {
				//확인 버튼
				view = LECT_VNONE;
			}
		}
		else {
			view = LECT_VNONE;
		}
		break;
	case LECT_OPTION:
		if (ButtonClick(point, v_option)) {
			//옵션 뷰
			if (ButtonClick(point, v_option_ok)) {
				//확인 버튼
				view = LECT_VNONE;
			}
		}
		else {
			view = LECT_VNONE;
		}
		break;
	default:
		if (ButtonClick(point, charInfo)) {
			//플레이어 정보
			view = LECT_CHARINFO;
		}
		else if (ButtonClick(point, option)) {
			//설정
			view = LECT_OPTION;
		}
		else if (ButtonClick(point, play)) {
			//시작
			gotoScene = LECT_SELECT;
		}
		break;
	}
}
