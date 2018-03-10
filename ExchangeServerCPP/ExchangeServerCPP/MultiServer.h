//
// Created by Shawn Manuel on 1/01/2018.
//

#ifndef SERVERPROGRAM_MULTISERVER_H
#define SERVERPROGRAM_MULTISERVER_H

#include "Server.h"
#include "Connection.h"
#include <vector>

class MultiServer : public Server
{
	protected:
		static void ListenForClients(LPVOID args);
		void AddClient(Connection* client);
		void RemoveClient(Connection* client);

    private:
        vector<Connection*> *clients;
		HANDLE listener;

    public:
		MultiServer(int port);
		void StartServer();
		void Broadcast(string message);
		void SendMessageTo(void *source, string message);
		virtual void OnNotify(void *source, string message) override;
		~MultiServer();
};

#endif //SERVERPROGRAM_MULTISERVER_H
