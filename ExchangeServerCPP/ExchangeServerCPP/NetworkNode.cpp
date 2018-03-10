//
// Created by Shawn Manuel on 30/12/2017.
//

#include "NetworkNode.h"

NetworkNode::NetworkNode()
{
	InitializeWinServer();
	Socket = GetTCPSocket();
}

bool NetworkNode::WinServerInitialized = false;

void NetworkNode::InitializeWinServer()
{
	if (!WinServerInitialized)
	{
		WSADATA wsData;
		WORD ver = MAKEWORD(2, 2);
		int wsok = WSAStartup(ver, &wsData);
		if (wsok != 0)
		{
			cerr << "Error initializing WSOK" << endl;
			exit(EXIT_FAILURE);
		}
		WinServerInitialized = true;
	}
}

SOCKET NetworkNode::GetTCPSocket()
{
	SOCKET Socket = socket(AF_INET, SOCK_STREAM, 0);
	if (Socket == INVALID_SOCKET)
	{
		cerr << "Error creating main socket" << endl;
		exit(EXIT_FAILURE);
	}
	return Socket;
}

bool NetworkNode::SendMessage(SOCKET Socket, string message)
{
	char buffer[BUFSIZ];
	ZeroMemory(buffer, BUFSIZ);
	strcpy_s(buffer, message.c_str());
	int bytes = send(Socket, buffer, BUFSIZ, 0);
	return bytes != SOCKET_ERROR;
}

sockaddr_in NetworkNode::GetSocketAddress(const char * IPaddress, int port)
{
	sockaddr_in socket_addr;
	socket_addr.sin_family = AF_INET;
	socket_addr.sin_port = htons(port);
	InetPton(AF_INET, IPaddress, &socket_addr.sin_addr.s_addr);
	return socket_addr;
}

NetworkNode::~NetworkNode()
{
}
