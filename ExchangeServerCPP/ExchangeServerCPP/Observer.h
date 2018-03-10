//
// Created by Shawn Manuel on 30/12/2017.
//

#ifndef SERVERPROGRAM_OBSERVER_H
#define SERVERPROGRAM_OBSERVER_H

#include <iostream>

using namespace std;

class Observer
{
	public:
		Observer();
		virtual void OnNotify(void *source, string msg);
		~Observer();
};

#endif //SERVERPROGRAM_OBSERVER_H