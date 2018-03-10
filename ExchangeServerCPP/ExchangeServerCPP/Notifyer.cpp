//
// Created by Shawn Manuel on 1/01/2018.
//

#include "Notifyer.h"

Notifyer::Notifyer()
{
	observers = vector<Observer*>();
}

void Notifyer::attach(Observer *o)
{
	observers.push_back(o);
}

void Notifyer::detatch(Observer *o)
{
	vector<Observer*>::iterator newEnd = remove(observers.begin(), observers.end(), o);
	observers.erase(newEnd, observers.end());
}

void Notifyer::notify(void *source, string msg)
{
	for (Observer *o : observers)
	{
		o->OnNotify(source, msg);
	}
}


Notifyer::~Notifyer()
{
}
