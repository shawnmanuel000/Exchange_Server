//
// Created by Shawn Manuel on 30/12/2017.
//

#ifndef SERVERPROGRAM_MARKETDATACLIENT_H
#define SERVERPROGRAM_MARKETDATACLIENT_H

#include "MarketDataServer.h"

class MarketDataClient : public MarketDataServer
{
	private:
		bool receivedFullPriceDepth;

	public:
		MarketDataClient(const char * serverIP, int serverPort, int hostPort);
		virtual void Run() override;
		virtual void OnNotify(void *source, string message) override;
};

#endif //SERVERPROGRAM_MARKETDATACLIENT_H