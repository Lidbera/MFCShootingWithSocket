#include "pch.h"
#include "Multi.h"

Multi::Multi() : Scene()
{
	Initialize();
}

Multi::Multi(Sound* sound) : Scene(sound)
{
	Initialize();
}

void Multi::Initialize()
{
	select = LECT_MNONE;
	input = false;
	inputDelay = 0;
	inputDelay2 = 0;
}

void Multi::AppendEndToIP(char b)
{
	int len;
	len = strlen(serverIP);
	if (len < 15) {
		serverIP[len] = b;
		serverIP[len + 1] = '\0';
	}

	inputDelay2 = 0;
	printf("serverIP: %s\n", serverIP);
}

void Multi::RemoveEndToIP()
{
	int i = 0;
	while (serverIP[i]) {
		i++;
	}
	if (i > 0) {
		serverIP[i - 1] = '\0';
	}

	inputDelay2 = 0;
	printf("serverIP: %s\n", serverIP);
}

void Multi::Draw(CDC* pDC, int wx, int wy)
{
	inputDelay2++;

	CDC memDC;
	memDC.CreateCompatibleDC(pDC);

	//SERVER
	rserver = Rect(15, wy / 2 - 100, wx / 2 - 15, wy / 2 + 100);
	DrawRectImage(pDC, &memDC, IDB_BTN, rserver);
	DrawRectText(pDC, &memDC, L"서버로 대기", 20, rserver);

	//CLIENT
	rclient = Rect(wx / 2 + 15, wy / 2 - 100, wx - 15, wy / 2 + 100);
	DrawRectImage(pDC, &memDC, IDB_BTN, rclient);
	DrawRectText(pDC, &memDC, L"클라이언트로 접속", 20, rclient);

	//BACK
	back = Rect(wx - 115, 15, wx - 15, 115);
	DrawRectImage(pDC, &memDC, IDB_CLOSEBTN, back);

	switch (view) {
	case LECT_IPINPUT:
		v_ipInput = Rect(100, 300, wx - 100, wy - 300);
		DrawRectImage(pDC, &memDC, IDB_PANEL, v_ipInput);
		CString str;
		str.Format(L"IP를 입력해주세요");
		DrawRectText(pDC, &memDC, str, 30, Rect(v_ipInput.l, v_ipInput.t, v_ipInput.r, v_ipInput.t + 150));
		//IP 입력창
		v_ipInputWindow = Rect(v_ipInput.l + 20, (v_ipInput.t + v_ipInput.b) / 2 - 80, v_ipInput.r - 20, (v_ipInput.t + v_ipInput.b) / 2 + 40);
		DrawRectImage(pDC, &memDC, IDB_SPANEL, v_ipInputWindow);
		if (input) {
			if (inputDelay < 40) {
				str.Format(L"%s", CString(serverIP));
				inputDelay++;
			}
			else if (inputDelay >= 40 && inputDelay < 80) {
				str.Format(L"%s|", CString(serverIP));
				inputDelay++;
			}
			else {
				str.Format(L"%s", CString(serverIP));
				inputDelay = 0;
			}
		}
		else {
			str.Format(L"%s", CString(serverIP));
		}
		DrawRectText(pDC, &memDC, str, 20, v_ipInputWindow);
		//확인
		v_ipInput_ok = Rect(v_ipInput.l + 20, v_ipInput.b - 100, (v_ipInput.l + v_ipInput.r) / 2 - 10, v_ipInput.b - 20);
		DrawRectImage(pDC, &memDC, IDB_BTN, v_ipInput_ok);
		DrawRectText(pDC, &memDC, L"확인", 20, v_ipInput_ok);
		//취소
		v_ipInput_cancel = Rect((v_ipInput.l + v_ipInput.r) / 2 + 10, v_ipInput.b - 100, v_ipInput.r - 20, v_ipInput.b - 20);
		DrawRectImage(pDC, &memDC, IDB_BTN, v_ipInput_cancel);
		DrawRectText(pDC, &memDC, L"취소", 20, v_ipInput_cancel);
		break;
	}

	memDC.DeleteDC();
}

void Multi::TimerCall(TIMER timer)
{
}

void Multi::Finish()
{
}

void Multi::KeyInput(WPARAM wParam)
{
	if (input && inputDelay2 > 8) {
		switch (wParam) {
		case 0x30:
			AppendEndToIP('0');
			break;
		case 0x31:
			AppendEndToIP('1');
			break;
		case 0x32:
			AppendEndToIP('2');
			break;
		case 0x33:
			AppendEndToIP('3');
			break;
		case 0x34:
			AppendEndToIP('4');
			break;
		case 0x35:
			AppendEndToIP('5');
			break;
		case 0x36:
			AppendEndToIP('6');
			break;
		case 0x37:
			AppendEndToIP('7');
			break;
		case 0x38:
			AppendEndToIP('8');
			break;
		case 0x39:
			AppendEndToIP('9');
			break;
		case 0x2E:
			AppendEndToIP('.');
			break;
		case 0x08:
			RemoveEndToIP();
			break;
		}
	}
}

void Multi::MouseClick(CPoint point)
{
	switch (view) {
	case LECT_IPINPUT:
		if (ButtonClick(point, v_ipInput)) {
			if (ButtonClick(point, v_ipInputWindow)) {
				//IP 입력
				input = true;
			}
			else if (ButtonClick(point, v_ipInput_ok)) {
				//확인 버튼 - 매칭으로
				server = false;
				gotoScene = LECT_MATCH;
			}
			else if (ButtonClick(point, v_ipInput_cancel)) {
				//취소 버튼
				input = false;
				view = LECT_VNONE;
			}
		}
		else {
			input = false;
			view = LECT_VNONE;
		}
		break;
	default:
		if (ButtonClick(point, rserver)) {
			//매칭-서버
			server = true;
			gotoScene = LECT_MATCH;
		}
		else if (ButtonClick(point, rclient)) {
			//매칭-클라
			server = false;
			view = LECT_IPINPUT;
		}
		else if (ButtonClick(point, back)) {
			//뒤로
			gotoScene = LECT_LOBBY;
		}
		break;
	}
}
