#include "pch.h"
#include "SocketClient.h"

#pragma comment(lib, "ws2_32")

SocketClient::SocketClient(Control* control) : Socket(control) {

	printf("ClientStarting¡¦\n");
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		Error("Start");
		return;
	}
	
	printf("ClientCreating¡¦\n");
	clientSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (clientSocket == INVALID_SOCKET) {
		Error("Socket");
		return;
	}

	memset(&serverAddress, 0, sizeof(SOCKADDR_IN));
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(PORT);
	printf("connect ½Ãµµ: %s\n", control->game->GetMyIP());
	serverAddress.sin_addr.s_addr = inet_addr(control->game->GetMyIP());

	printf("ClientConnecting¡¦\n");
	if (connect(clientSocket, (SOCKADDR*)& serverAddress, sizeof(serverAddress)) == SOCKET_ERROR) {
		Error("connect");
		return;
	}

	printf("NoErrorForSocket\n");
	control->game->gotoScene = LECT_INGAMEMULTIC;
}

bool SocketClient::Commun()
{
	Data data = control->GetData();
	send(clientSocket, (char*)&data, sizeof(data), 0);
	if (control->me.shot) {
		control->me.shot = false;
	}

	recv(clientSocket, (char*)&data, sizeof(data), 0);
	control->RecvData(data);

	return true;
}

void SocketClient::Close()
{
	closesocket(clientSocket);
	WSACleanup();
}
