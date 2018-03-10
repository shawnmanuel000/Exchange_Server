//
// Created by Shawn Manuel on 30/12/2017.
//

#include "Client.h"

Client::Client() : NetworkNode()
{
}

Client::Client(const char * IPaddress, int port)
{
	ConnectToHost(IPaddress, port);
}

void Client::Sender(LPVOID args)
{
	Client *c = (Client*)args;
	string input;
	do {
		cin >> input;
	} while (c->SendMessage(input));
}

void Client::Receive(LPVOID args)
{
	try
	{
		Client *c = (Client*)args;
		char buffer[BUFSIZ];
		cout << "Receiver Active" << endl;
		while (recv(c->Socket, buffer, BUFSIZ, 0) != SOCKET_ERROR)
		{
			c->notify(c, buffer);
			ZeroMemory(buffer, BUFSIZ);
		}
	}
	catch (exception ex)
	{
		cout << "Connection closed: " << ex.what() << endl;
		ExitThread(1);
	}
	cout << "Closing thread" << endl;
	ExitThread(0);
}

void Client::RegisterSender(LPTHREAD_START_ROUTINE fn, LPVOID args)
{
	if (!SenderActive())
	{
		sender = CreateThread(NULL, 0, fn, args, 0, NULL);
	}
}

void Client::RegisterReceiver(LPTHREAD_START_ROUTINE fn, LPVOID args)
{
	if (!ReceiverActive())
	{
		receiver = CreateThread(NULL, 0, fn, args, 0, NULL);
	}
}

void Client::ConnectToHost(const char* IPaddress, int port)
{
	sockaddr_in server_addr = GetSocketAddress(IPaddress, port);
    if(connect(Socket, (const struct sockaddr *) &server_addr, (socklen_t)sizeof(server_addr)) == SOCKET_ERROR)
    {
        cout << "Connection to server failed" << endl;
		exit(-1);
    }
	cout << "Client active" << endl;
}

void Client::StartClient(bool waitForAllThreads, bool registerSender)
{
	RegisterReceiver((LPTHREAD_START_ROUTINE)Receive, this);
	
	if (registerSender)
	{
		RegisterSender((LPTHREAD_START_ROUTINE)Sender, this);
	}

	if (waitForAllThreads)
	{
		if (registerSender)
		{
			WaitForMultipleObjects(2, new HANDLE[2]{ receiver, sender }, FALSE, INFINITE);
		}
		else
		{
			WaitForSingleObject(receiver, INFINITE);
		}
	}
}

bool Client::SenderActive()
{
	return sender != NULL;
}

bool Client::ReceiverActive()
{
	return receiver != NULL;
}

bool Client::SendMessage(string message)
{
	return NetworkNode::SendMessage(Socket, message);
}

void Client::OnNotify(void *source, string message)
{
	cout << "[Client]: " << message << endl;
}


void Client::Stop(DWORD returnValue)
{
	TerminateThread(this->receiver, returnValue);
	TerminateThread(this->sender, returnValue);
	receiver = NULL;
	sender = NULL;
}

Client::~Client()
{
}