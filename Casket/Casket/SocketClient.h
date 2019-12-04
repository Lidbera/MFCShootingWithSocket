#include "Socket.h"

#pragma once
class SocketClient : public Socket
{
public:
	SocketClient(Control *control);
	virtual bool Commun() override;
	virtual void Close() override;

private:
	SOCKET clientSocket;
	SOCKADDR_IN serverAddress;
};