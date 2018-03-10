//
// Created by Shawn Manuel on 30/12/2017.
//

#ifndef SERVERPROGRAM_NOTIFYER_H
#define SERVERPROGRAM_NOTIFYER_H

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <algorithm>

#include "Observer.h"

using namespace std;

class Notifyer
{
	private:
		vector<Observer*> observers;

	public:
		Notifyer();
		virtual void attach(Observer *o);
		virtual void detatch(Observer *o);
		virtual void notify(void *source, string msg);
		~Notifyer();
};

#endif //SERVERPROGRAM_NOTIFYER_H

