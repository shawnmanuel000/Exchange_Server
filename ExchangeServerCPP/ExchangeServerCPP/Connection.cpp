//
// Created by Shawn Manuel on 1/01/2018.
//

#include "Connection.h"

Connection::Connection(SOCKET socket) : Client()
{
	this->Socket = socket;
}

Connection::~Connection()
{
}
