//
// Created by Shawn Manuel on 30/12/2017.
//

#ifndef SERVERPROGRAM_EXCHANGE_H
#define SERVERPROGRAM_EXCHANGE_H

#include <list>
#include "MultiServer.h"
#include "PriceDepthList.h"

class Exchange
{
	protected:
		shared_ptr<MultiServer> server;
		shared_ptr<PriceDepthList> pd;
	public:
		Exchange(int port);
		virtual void Run();
		~Exchange();
};

#endif //SERVERPROGRAM_EXCHANGE_H