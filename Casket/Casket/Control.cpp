#include "pch.h"
#include "Control.h"

Control::Control()
{
	//NOT USE
	Initialize(nullptr);
}

Control::Control(Sound* sound)
{
	Initialize(sound);
}

void Control::Initialize(Sound* _sound)
{
	socket = LECT_WAIT;
	scene = LECT_LOBBY;
	sound = _sound;
	me = Player(IDB_CHAR, 3, 3);
	game = new Lobby(sound);	
}

void Control::Draw(CDC* pDC, int wx, int wy)
{
	game->Draw(pDC, wx, wy);

	//�� �̵�
	switch (game->gotoScene) {
	case LECT_LOBBY:
		delete game;
		scene = LECT_LOBBY;
		game = new Lobby(sound);
		break;
	case LECT_SELECT:
		delete game;
		scene = LECT_SELECT;
		game = new Select(sound);
		break;
	case LECT_MULTI:
		delete game;
		scene = LECT_MULTI;
		game = new Multi(sound);
		break;
	case LECT_MATCH:
		server = game->server;
		serverIP = game->serverIP;
		delete game;
		scene = LECT_MATCH;
		game = new Match(sound);
		game->server = server;
		for (int i = 0; i < 15; i++) {
			game->serverIP[i] = serverIP[i];
		}
		break;
	case LECT_INGAMESINGLE:
		delete game;
		scene = LECT_INGAMESINGLE;
		game = new Ingame(sound, &me);
		break;
	case LECT_INGAMEMULTIC:
		delete game;
		server = false;
		game->server = false;
		scene = LECT_INGAMEMULTI;
		game = new Ingame(sound, &me, &you, false);
		socket = LECT_PLAYING;
		break;
	case LECT_INGAMEMULTIS:
		delete game;
		server = true;
		game->server = true;
		scene = LECT_INGAMEMULTI;
		game = new Ingame(sound, &me, &you, true);
		socket = LECT_PLAYING;
		break;
	}

	switch (game->charSelect) {
	case LECT_LEFTBTN:
		//ĳ���� ����-��
		game->charSelect = LECT_CNONE;
		me = Player(IDB_BTN, 3, 3);
		break;
	case LECT_RIGHTBTN:
		//ĳ���� ����-��
		game->charSelect = LECT_CNONE;
		me = Player(IDB_BTN, 3, 3);
		break;
	}

	if (!once) {
		//����
	}
	if (game->matchLoaded) {
		game->matchLoaded = false;
		if (game->server) {
			socket = LECT_SERVER;
		}
		else {
			socket = LECT_CLIENT;
		}
		once = true;
	}

	if (game->socketBreak) {
		game->socketBreak = false;
		socket = LECT_SOCKETBREAK;
	}
}

void Control::TimerCall(TIMER timer)
{
	game->TimerCall(timer);
}

void Control::Finish()
{
	game->Finish();
}

void Control::KeyInput(bool b, KEY key)
{
	game->KeyInput(b, key);
	if (scene == LECT_INGAMEMULTI) {
		sendData = true;
	}
}

void Control::KeyInput(WPARAM wParam)
{
	game->KeyInput(wParam);
}

void Control::MouseClick(CPoint point)
{
	game->MouseClick(point);
}

#pragma region Socket ����

void Control::ServerDisconnect()
{
	printf("disconnect");
	//���� ����. ���� ����Ұ��� �׸��Ұ��� ���������
	socket = LECT_SOCKETBREAK;
	you = Player();
}

Data Control::GetData()
{
	//�ش� �÷��̾� ������ �ѱ�
	DataForClient dfc = DataForClient();
	if (server) {
		if (game->dfc.bossBmpID != -1) {
			dfc = game->dfc;
		}
	}
	return Data(me, dfc);
}

void Control::RecvData(Data data)
{
	//��� �÷��̾� ������ ����
	you = data.player;
	if (!server) {
		game->dfc = data.dfc;
	}
}

#pragma endregion