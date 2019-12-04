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
	LECT_LOBBY, //로비
	LECT_SELECT, //솔로 혹은 멀티 선택
	LECT_MULTI, //서버(대기), 클라(IP입력) 선택
	LECT_MATCH, //서버 연결 중
	LECT_INGAMESINGLE, //인게임-싱글
	LECT_INGAMEMULTI, //인게임-멀티
	LECT_INGAMEMULTIS, //-서버
	LECT_INGAMEMULTIC //-클라
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