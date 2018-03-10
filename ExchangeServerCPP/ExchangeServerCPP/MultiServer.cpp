//
// Created by Shawn Manuel on 1/01/2018.
//

#include "MultiServer.h"

MultiServer::MultiServer(int port) : Server(port)
{
    clients = new vector<Connection*>();
}

void MultiServer::StartServer()
{
	ConnectToSocket();
	listen(Socket, SOMAXCONN);

	listener = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ListenForClients, this, 0, NULL);
}

void MultiServer::Broadcast(string message)
{
	for (int i = clients->size()-1; i >= 0; i--)
	{
		Connection *con = (*clients)[i];
		if (!con->SendMessage(message))
		{
			RemoveClient(con);
		}
	}
}

void MultiServer::SendMessageTo(void * source, string message)
{
	Client *c = (Client*)source;
	c->SendMessage(message);
}

void MultiServer::ListenForClients(LPVOID args)
{
	cout << "MultiServer Waiting for connection..." << endl;
	try
	{
		MultiServer ms = *((MultiServer*)args);
		do {
			SOCKET client = ms.WaitForClient();
			Connection *con = new Connection(client);
			ms.AddClient(con);
		} while (ms.Socket != SOCKET_ERROR);
	}
	catch (...)
	{
		cout << "Connection closed" << endl;
	}
	cout << "Exiting listener" << endl;
}

void MultiServer::AddClient(Connection * con)
{
	cout << "Adding " << clients->size();
	con->attach(this);
	con->StartClient(false, false);
	clients->push_back(con);
	cout << "-> " << clients->size() << endl;
}

void MultiServer::RemoveClient(Connection * con)
{
	cout << "Removing " << clients->size();
	con->detatch(this);
	con->Stop(0);
	vector<Connection*>::iterator newEnd = remove(clients->begin(), clients->end(), con);
	clients->erase(newEnd, clients->end());
	delete con;
	cout << "-> " << clients->size() << endl;
}

void MultiServer::OnNotify(void *source, string message)
{
	cout << "[Multiserver]: " << message << endl;
	if (message == "FULL")
	{
		notify(source, message);
	}
}

MultiServer::~MultiServer()
{
}

