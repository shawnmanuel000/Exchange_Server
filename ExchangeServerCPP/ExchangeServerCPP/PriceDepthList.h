//
// Created by Shawn Manuel on 30/12/2017.
//

#ifndef SERVERPROGRAM_PRICEDEPTHLIST_H
#define SERVERPROGRAM_PRICEDEPTHLIST_H

#include <cstdio>
#include <cstdlib>
#include <sstream>
#include <iostream>
#include <string>
#include <forward_list>
#include <time.h>
#include "LinkedList.h"

using namespace std;

class PriceDepthList
{
	private:
		LinkedList<pair<int, int>> *buys;
		LinkedList<pair<int, int>> *sells;
		void MakeRandomChanges(LinkedList<pair<int, int>> *l);
		int GetRandomQty();
		int Length(LinkedList<pair<int, int>> *l);
		string ToString(LinkedList<pair<int, int>> *l);
		string GetChanges(LinkedList<pair<int, int>> *list, LinkedList<pair<int, int>> *news, int& numchanges);
		void SplitLineIntoBuysAndSells(string line, LinkedList<pair<int, int>> *buys, LinkedList<pair<int, int>> *sells);
		void ParseChangesSingleList(LinkedList<pair<int, int>> *list, LinkedList<pair<int, int>> *news);

	public:
		PriceDepthList();
		string ParseString(string input);
		void ParseChangesOnly(string input);
		void MakeRandomChanges();
		static forward_list<int>* StringToIntArray(string str);
		string ToString();
		~PriceDepthList();
};

#endif //SERVERPROGRAM_PRICEDEPTHLIST_H