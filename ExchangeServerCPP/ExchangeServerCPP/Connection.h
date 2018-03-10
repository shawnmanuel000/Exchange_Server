//
// Created by Shawn Manuel on 1/01/2018.
//

#ifndef SERVERPROGRAM_CONNECTION_H
#define SERVERPROGRAM_CONNECTION_H

#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <sys/types.h>
#include <string>
#include <thread>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")

#include "Client.h"

using namespace std;

class Connection : public Client
{
	public:
		Connection(SOCKET socket);
		~Connection();
};

#endif //SERVERPROGRAM_CONNECTION_H
