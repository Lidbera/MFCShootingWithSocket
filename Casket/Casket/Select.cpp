#include "pch.h"
#include "Select.h"

Select::Select() : Scene()
{
}

Select::Select(Sound* sound) : Scene(sound)
{
}

void Select::Initialize()
{
}

void Select::Draw(CDC* pDC, int wx, int wy)
{
	CDC memDC;
	memDC.CreateCompatibleDC(pDC);

	//CHARACTER
	character = Rect(0, 0, wx, wy);
	DrawRectImage(pDC, &memDC, 0, character); //캐릭터 배경으로 바꿔야

	//LEFT
	left = Rect(10, wy / 2 - 75, 85, wy / 2 + 75);
	DrawRectImage(pDC, &memDC, IDB_LEFT, left);

	//RIGHT
	right = Rect(wx - 85, wy / 2 - 75, wx - 10, wy / 2 + 75);
	DrawRectImage(pDC, &memDC, IDB_RIGHT, right);

	//SINGLE
	single = Rect(15, wy - 130, wx / 2 - 5, wy - 10);
	DrawRectImage(pDC, &memDC, IDB_BTN, single);
	DrawRectText(pDC, &memDC, L"싱글", 20, single);

	//MULTI
	multi = Rect(wx / 2 + 5, wy - 130, wx - 15, wy - 10);
	DrawRectImage(pDC, &memDC, IDB_BTN, multi);
	DrawRectText(pDC, &memDC, L"멀티", 20, multi);

	//BACK
	back = Rect(wx - 115, 15, wx - 15, 115);
	DrawRectImage(pDC, &memDC, IDB_CLOSEBTN, back);

	switch (view) {
	case LECT_SINGLECHECK:
		v_singleCheck = Rect(100, 300, wx - 100, wy - 300);
		DrawRectImage(pDC, &memDC, IDB_PANEL, v_singleCheck);
		DrawRectText(pDC, &memDC, L"싱글 플레이로\n 시작합니까?", 20, v_singleCheck);
		//확인
		v_singleCheck_ok = Rect(v_singleCheck.l + 20, v_singleCheck.b - 100, (v_singleCheck.l + v_singleCheck.r) / 2 - 10, v_singleCheck.b - 20);
		DrawRectImage(pDC, &memDC, IDB_BTN, v_singleCheck_ok);
		DrawRectText(pDC, &memDC, L"확인", 20, v_singleCheck_ok);
		//취소
		v_singleCheck_cancel = Rect((v_singleCheck.l + v_singleCheck.r) / 2 + 10, v_singleCheck.b - 100, v_singleCheck.r - 20, v_singleCheck.b - 20);
		DrawRectImage(pDC, &memDC, IDB_BTN, v_singleCheck_cancel);
		DrawRectText(pDC, &memDC, L"취소", 20, v_singleCheck_cancel);
		break;
	}

	memDC.DeleteDC();
}

void Select::TimerCall(TIMER timer)
{
}

void Select::Finish()
{
}

void Select::MouseClick(CPoint point)
{
	switch (view) {
	case LECT_SINGLECHECK:
		if (ButtonClick(point, v_singleCheck)) {
			//싱글 확인 체크
			if (ButtonClick(point, v_singleCheck_ok)) {
				//확인 버튼 - 게임으로
				gotoScene = LECT_INGAMESINGLE;
			}
			else if (ButtonClick(point, v_singleCheck_cancel)) {
				//취소 버튼
				view = LECT_VNONE;
			}
		}
		else {
			view = LECT_VNONE;
		}
		break;
	default:
		if (ButtonClick(point, left)) {
			//캐릭터 변경-좌
			//
		}
		else if (ButtonClick(point, right)) {
			//캐릭터 변경-우
			//
		}
		else if (ButtonClick(point, single)) {
			//게임 시작-싱글
			view = LECT_SINGLECHECK;
		}
		else if (ButtonClick(point, multi)) {
			//게임 시작-멀티
			gotoScene = LECT_MULTI;
		}
		else if (ButtonClick(point, back)) {
			//뒤로
			gotoScene = LECT_LOBBY;
		}
		break;
	}
}
