//
// Created by Shawn Manuel on 30/12/2017.
//

#ifndef SERVERPROGRAM_SERVER_H
#define SERVERPROGRAM_SERVER_H

#include "Client.h"

using namespace std;

class Server : public NetworkNode
{
    private:
        int port;
		sockaddr_in server_addr;
		socklen_t size;

	protected:
		SOCKET WaitForClient();

    public:
        Server(int port);
        void StartServer();
		void ConnectToSocket();
        void run(int client);
		~Server();
};

#endif //SERVERPROGRAM_SERVER_H
