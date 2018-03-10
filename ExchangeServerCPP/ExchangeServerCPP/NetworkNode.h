//
// Created by Shawn Manuel on 30/12/2017.
//

#ifndef SERVERPROGRAM_NETWORKNODE_H
#define SERVERPROGRAM_NETWORKNODE_H

#include <sys/types.h>
#include <string>
#include <thread>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")

#include "Notifyer.h"
#include "Observer.h"

using namespace std;

class NetworkNode: public Notifyer, public Observer
{
	protected:
		SOCKET Socket;
	private:
		void InitializeWinServer();
	public:
		NetworkNode();
		static SOCKET GetTCPSocket();
		static bool WinServerInitialized;
		static sockaddr_in GetSocketAddress(const char* IPaddress, int port);
		static bool SendMessage(SOCKET Socket, string message);
		~NetworkNode();
};

#endif //SERVERPROGRAM_NETWORKNODE_H