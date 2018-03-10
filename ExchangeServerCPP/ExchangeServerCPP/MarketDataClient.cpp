#include "MarketDataClient.h"
#include "String.h"

MarketDataClient::MarketDataClient(const char * serverIP, int serverPort, int hostPort) 
	: MarketDataServer(serverIP, serverPort, hostPort)
{
	receivedFullPriceDepth = false;
}

void MarketDataClient::Run()
{
	attach(this);
	StartClient(true, false);	
}

void MarketDataClient::OnNotify(void * source, string message)
{
	vector<string> fields = String::stringSplit(message, "|");
	if (fields.size() > 1 && fields[0] == string("FULL"))
	{
		pd->ParseString(fields[1]);
		receivedFullPriceDepth = true;
		cout << "initialized" << endl;
	}
	else if (receivedFullPriceDepth)
	{
		pd->ParseChangesOnly(message);
		cout << pd->ToString() << endl;
	}
	else
	{
		SendMessage("FULL");
	}
}


