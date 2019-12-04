#include "Socket.h"

#pragma once
class SocketServer : public Socket
{
public:
	SocketServer(Control* control);
	virtual bool Commun() override;
	virtual void Close() override;

private:
	SOCKET serverSocket; //�ٸ� ��ǻ�ͷκ��� ������ ���� ���� ��û�� �������ִ� ����
	SOCKET clientSocket;
	SOCKADDR_IN serverAddress; //������ ������Ҹ� ���� ����ü
	SOCKADDR_IN clientAddress; //Ŭ���̾�Ʈ�� �ּ����� ����ü
};

