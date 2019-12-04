#include <WinSock2.h>
#include "Control.h"
#include "Data.h"

#pragma once

#define PORT 9729
#define PACKET_SIZE 1024

class Socket
{
public:
	Socket();
	Socket(Control* control);
	void Error(char* msg);
	void ErrQuit(char* msg);
	virtual bool Commun();
	virtual void Close();

public:
	bool error;

protected:
	Control *control;
	WSADATA wsaData; //���� �ʱ�ȭ ������ �����ϱ� ���� ����ü
};