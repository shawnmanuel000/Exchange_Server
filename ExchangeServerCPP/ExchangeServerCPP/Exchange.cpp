#include "Exchange.h"

Exchange::Exchange(int port)
{
	server = make_shared<MultiServer>(port);
	pd = make_shared<PriceDepthList>();
}

void Exchange::Run()
{
	server->StartServer();
	pd->ParseString("4 5 28 1000 27 300 25 5000 24 300 30 500 31 2000 32 10000 33 50000 34 75000");
	int i = 0;
	while (true)
	{
		pd->MakeRandomChanges();
		string s = pd->ToString();
		server->Broadcast(s);
		cout << s << endl;
		Sleep(1000);
	}
}

Exchange::~Exchange()
{
}
