//
// Created by Shawn Manuel on 30/12/2017.
//

#include "Server.h"

Server::Server(int port)
{
    this->port = port;
	this->server_addr = GetSocketAddress("127.0.0.1", port);
	this->size = sizeof(server_addr);
}

void Server::StartServer()
{
	ConnectToSocket();
    listen(Socket, SOMAXCONN);

    cout << "Waiting for connection..." << endl;
    try
    {
		SOCKET client = WaitForClient();
        run(client);
    }
    catch(...)
    {
        cout << "Connection closed" << endl;
    }
}

void Server::ConnectToSocket()
{
	int bindSuccess = bind(Socket, (const sockaddr*)&server_addr, size);
    if(bindSuccess < 0)
    {
        cout << "Error binding socket" << endl;
        exit(EXIT_FAILURE);
    }
}

SOCKET Server::WaitForClient()
{
	SOCKET client = accept(Socket, (sockaddr*)&server_addr, &size);
	if (client == SOCKET_ERROR)
	{
		cout << "Error accepting" << endl;
		exit(EXIT_FAILURE);
	}
	return client;
}

void Server::run(int client)
{
	SendMessage(Socket, string("Server connected"));

    cout << "Connected to client..." << endl;

    while(Socket != SOCKET_ERROR)
    {
		SendMessage(Socket, string("Exchange"));
		Sleep(1000);
    }
}

Server::~Server()
{
}
