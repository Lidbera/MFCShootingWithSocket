#include "Socket.h"

#pragma once
class SocketServer : public Socket
{
public:
	SocketServer(Control* control);
	virtual bool Commun() override;
	virtual void Close() override;

private:
	SOCKET serverSocket; //다른 컴퓨터로부터 들어오는 접속 승인 요청을 수락해주는 소켓
	SOCKET clientSocket;
	SOCKADDR_IN serverAddress; //소켓의 구성요소를 담을 구조체
	SOCKADDR_IN clientAddress; //클라이언트측 주소정보 구조체
};

