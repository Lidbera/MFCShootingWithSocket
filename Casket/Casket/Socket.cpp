#include "pch.h"
#include "Socket.h"

Socket::Socket()
{
	//NOT USE
}

Socket::Socket(Control* _control)
{
	control = _control;
	error = false;
}

void Socket::Error(char* msg)
{
	int errorCode = WSAGetLastError();
	printf("Error: %s, (%d)\n", msg, errorCode);
	error = true;
}

void Socket::ErrQuit(char* msg)
{
	LPVOID lpMsgBuf;

	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,

		NULL, WSAGetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),

		(LPTSTR)& lpMsgBuf, 0, NULL);

	MessageBox(NULL, (LPCTSTR)lpMsgBuf, (LPCTSTR)msg, MB_ICONERROR);
	printf((char*)lpMsgBuf);

	LocalFree(lpMsgBuf);

	exit(-1);
}

bool Socket::Commun()
{
	//NOT USE
	return false;
}

void Socket::Close()
{
	//NOT USE
}
