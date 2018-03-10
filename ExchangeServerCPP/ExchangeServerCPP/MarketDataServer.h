//
// Created by Shawn Manuel on 30/12/2017.
//

#ifndef SERVERPROGRAM_MARKETDATASERVER_H
#define SERVERPROGRAM_MARKETDATASERVER_H

#include "Client.h"
#include "Exchange.h"

class MarketDataServer : public Exchange, public Client
{
	public:
		MarketDataServer(const char * serverIP, int serverPort, int hostPort);
		virtual void Run() override;
		virtual void OnNotify(void *source, string message) override;
		~MarketDataServer();
};

#endif //SERVERPROGRAM_MARKETDATASERVER_H