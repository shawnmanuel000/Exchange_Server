#include "MarketDataServer.h"



MarketDataServer::MarketDataServer(const char * serverIP, int serverPort, int hostPort) 
	: Client(serverIP, serverPort), Exchange(hostPort)
{
}

void MarketDataServer::Run()
{
	attach(this);
	server->attach(this);
	server->StartServer();
	StartClient(true, false);
}

void MarketDataServer::OnNotify(void * source, string message)
{
	cout << "[MarketDataServer]: " << message << endl;
	if (message == string("FULL"))
	{
		string reply = string("FULL|").append(pd->ToString());
		server->SendMessageTo(source, reply);
	}
	else
	{
		string changes = pd->ParseString(message);
		server->Broadcast(changes);
	}
}

MarketDataServer::~MarketDataServer()
{
}
