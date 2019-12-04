#include "pch.h"
#include "SocketServer.h"

#pragma comment(lib, "ws2_32")

SocketServer::SocketServer(Control* control) : Socket(control) {

	printf("ServerStarting¡¦\n");
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		Error("Start");
		return;
	}

	printf("ServerCreating¡¦\n");
	serverSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (serverSocket == INVALID_SOCKET) {
		Error("InvalidSocket");
		return;
	}

	memset(&serverAddress, 0, sizeof(SOCKADDR_IN));
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(PORT);
	serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);

	printf("ServerConnecting¡¦\n");
	if (bind(serverSocket, (SOCKADDR*)& serverAddress, sizeof(serverAddress)) == SOCKET_ERROR) {
		Error("Bind");
		return;
	}
	if (listen(serverSocket, 2) == SOCKET_ERROR) {
		Error("Listen");
		return;
	}

	clientAddress = {};
	int iClientSize = sizeof(clientAddress);
	clientSocket = accept(serverSocket, (SOCKADDR*)& clientAddress, &iClientSize);
	if (clientSocket == INVALID_SOCKET) {
		Error("Accept");
		return;
	}

	printf("NoErrorForSocket\n");
	control->game->gotoScene = LECT_INGAMEMULTIS;
}

bool SocketServer::Commun()
{
	Data data;
	recv(clientSocket, (char*)&data, sizeof(data), 0);
	control->RecvData(data);

	data = control->GetData();
	send(clientSocket, (char*)&data, sizeof(data), 0);
	if (control->me.shot) {
		control->me.shot = false;
	}
	if (control->game->dfc.shot) {
		control->game->dfc.shot = false;
	}
	if (control->game->dfc.shot2) {
		control->game->dfc.shot2 = false;
	}
	if (control->game->dfc.shot3) {
		control->game->dfc.shot3 = false;
	}
	if (control->game->dfc.shot4) {
		control->game->dfc.shot4 = false;
	}

	return true;
}

void SocketServer::Close()
{
	closesocket(clientSocket);
	closesocket(serverSocket);

	WSACleanup();
}

