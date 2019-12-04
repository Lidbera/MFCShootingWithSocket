#pragma once

struct Coord {
public:
	short x, y;
	Coord() {
		x = 0;
		y = 0;
	}
	Coord(int _x, int _y) {
		x = _x;
		y = _y;
	}
	Coord operator+(Coord a) {
		return Coord(x + a.x, y + a.y);
	}
};

struct DataForClient {
public:
	int bossBmpID;
	short bosshp, bossahp;
	Coord pos;
	bool shot, shot2, shot3, shot4;

	DataForClient() {
		bossBmpID = -1;
		bosshp = 999;
		bossahp = 999;
		pos = Coord();
	}
	DataForClient(int _bossBmpID, short _bosshp, short _bossahp, Coord _pos) {
		bossBmpID = _bossBmpID;
		bosshp = _bosshp;
		bossahp = _bossahp;
		pos = _pos;
	}

	void ToString() {
		printf("bossid: %d, hp:, %d, ahp: %d, pos: (%d,%d)\n", bossBmpID, bosshp, bossahp, pos.x, pos.y);
	}
};

struct Player {
public:
	bool alive;
	Coord pos;
	int bmpID;
	short life, bomb;
	bool shot, bshot;

	Player() {
		alive = false;
		pos = Coord();
		bmpID = 0;
		life = 0;
		bomb = 0;
		shot = false;
		bshot = false;
	}
	Player(int _bmpID, short _life, short _bomb) {
		alive = true;
		pos = Coord();
		bmpID = _bmpID;
		life = _life;
		bomb = _bomb;
		shot = false;
		bshot = false;
	}
	Player(bool a, short x, short y, int b, short l, short bm, bool s, bool bs) {
		alive = a;
		pos.x = x;
		pos.y = y;
		bmpID = b;
		life = l;
		bomb = bm;
		shot = s;
		bshot = bs;
	}

	void ToString() {
		printf("life: %d, shot: %d, bshot: %d\n", life, shot, bshot);
	}
};

struct Data {
	Player player;
	DataForClient dfc;

	Data() {
		player = Player();
		dfc = DataForClient();
	}
	Data(Player _player, DataForClient _dfc) {
		player = _player;
		dfc = _dfc;
	}
};