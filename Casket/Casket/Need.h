#pragma once

enum TIMER {
	LECT_MOVEMENT,
	LECT_STAGE,
	LECT_DRAW
};

enum KEY {
	LECT_UP,
	LECT_DOWN,
	LECT_LEFT,
	LECT_RIGHT,
	LECT_SPACE
};

struct Rect {
public:
	int l, t, r, b;
	Rect() {
		l = 0;
		t = 0;
		r = 0;
		b = 0;
	}
	Rect(int _l, int _t, int _r, int _b) {
		l = _l;
		t = _t;
		r = _r;
		b = _b;
	}
};

enum SOCKETFORCONTROL {
	LECT_WAIT,
	LECT_SERVER,
	LECT_CLIENT,
	LECT_PLAYING,
	LECT_SOCKETBREAK
};

enum SCENE {
	LECT_SNONE,
	LECT_LOBBY, //�κ�
	LECT_SELECT, //�ַ� Ȥ�� ��Ƽ ����
	LECT_MULTI, //����(���), Ŭ��(IP�Է�) ����
	LECT_MATCH, //���� ���� ��
	LECT_INGAMESINGLE, //�ΰ���-�̱�
	LECT_INGAMEMULTI, //�ΰ���-��Ƽ
	LECT_INGAMEMULTIS, //-����
	LECT_INGAMEMULTIC //-Ŭ��
};

enum VIEW {
	LECT_VNONE,
	LECT_CHARINFO,
	LECT_OPTION,
	LECT_SINGLECHECK,
	LECT_IPINPUT,
	LECT_PAUSE
};

enum CHARSELECT {
	LECT_CNONE,
	LECT_LEFTBTN,
	LECT_RIGHTBTN
};

enum MULTISELECT {
	LECT_MNONE,
	LECT_MSERVER,
	LECT_MCLIENT
};

enum CHARACTER {

};

enum BULLET {
	LECT_P1BULLET,
	LECT_P2BULLET,
	LECT_B1BULLET,
	LECT_B2BULLET
};