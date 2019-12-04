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
	DrawRectImage(pDC, &memDC, 0, character); //ĳ���� ������� �ٲ��

	//LEFT
	left = Rect(10, wy / 2 - 75, 85, wy / 2 + 75);
	DrawRectImage(pDC, &memDC, IDB_LEFT, left);

	//RIGHT
	right = Rect(wx - 85, wy / 2 - 75, wx - 10, wy / 2 + 75);
	DrawRectImage(pDC, &memDC, IDB_RIGHT, right);

	//SINGLE
	single = Rect(15, wy - 130, wx / 2 - 5, wy - 10);
	DrawRectImage(pDC, &memDC, IDB_BTN, single);
	DrawRectText(pDC, &memDC, L"�̱�", 20, single);

	//MULTI
	multi = Rect(wx / 2 + 5, wy - 130, wx - 15, wy - 10);
	DrawRectImage(pDC, &memDC, IDB_BTN, multi);
	DrawRectText(pDC, &memDC, L"��Ƽ", 20, multi);

	//BACK
	back = Rect(wx - 115, 15, wx - 15, 115);
	DrawRectImage(pDC, &memDC, IDB_CLOSEBTN, back);

	switch (view) {
	case LECT_SINGLECHECK:
		v_singleCheck = Rect(100, 300, wx - 100, wy - 300);
		DrawRectImage(pDC, &memDC, IDB_PANEL, v_singleCheck);
		DrawRectText(pDC, &memDC, L"�̱� �÷��̷�\n �����մϱ�?", 20, v_singleCheck);
		//Ȯ��
		v_singleCheck_ok = Rect(v_singleCheck.l + 20, v_singleCheck.b - 100, (v_singleCheck.l + v_singleCheck.r) / 2 - 10, v_singleCheck.b - 20);
		DrawRectImage(pDC, &memDC, IDB_BTN, v_singleCheck_ok);
		DrawRectText(pDC, &memDC, L"Ȯ��", 20, v_singleCheck_ok);
		//���
		v_singleCheck_cancel = Rect((v_singleCheck.l + v_singleCheck.r) / 2 + 10, v_singleCheck.b - 100, v_singleCheck.r - 20, v_singleCheck.b - 20);
		DrawRectImage(pDC, &memDC, IDB_BTN, v_singleCheck_cancel);
		DrawRectText(pDC, &memDC, L"���", 20, v_singleCheck_cancel);
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
			//�̱� Ȯ�� üũ
			if (ButtonClick(point, v_singleCheck_ok)) {
				//Ȯ�� ��ư - ��������
				gotoScene = LECT_INGAMESINGLE;
			}
			else if (ButtonClick(point, v_singleCheck_cancel)) {
				//��� ��ư
				view = LECT_VNONE;
			}
		}
		else {
			view = LECT_VNONE;
		}
		break;
	default:
		if (ButtonClick(point, left)) {
			//ĳ���� ����-��
			//
		}
		else if (ButtonClick(point, right)) {
			//ĳ���� ����-��
			//
		}
		else if (ButtonClick(point, single)) {
			//���� ����-�̱�
			view = LECT_SINGLECHECK;
		}
		else if (ButtonClick(point, multi)) {
			//���� ����-��Ƽ
			gotoScene = LECT_MULTI;
		}
		else if (ButtonClick(point, back)) {
			//�ڷ�
			gotoScene = LECT_LOBBY;
		}
		break;
	}
}
