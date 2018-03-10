#include <iostream>
#include "Server.h"
#include "Client.h"
#include "MarketDataClient.h"
#include "Exchange.h"
#include "PriceDepthList.h"

using namespace std;

int main(int argc, char *argv[])
{
    if(argc == 2)
    {
		Exchange *e = new Exchange(atoi(argv[1]));
		e->Run();
    }
	else if (argc == 3)
	{
		MarketDataClient *c = new MarketDataClient("127.0.0.1", atoi(argv[2]), 0);
		c->Run();
	}
	else if(argc == 4)
    {
		MarketDataServer *s = new MarketDataServer("127.0.0.1", atoi(argv[2]), atoi(argv[3]));
        s->Run();
    }
    return 0;
}