#include "PriceDepthList.h"

PriceDepthList::PriceDepthList()
{
	buys = new LinkedList<pair<int, int>>();
	sells = new LinkedList<pair<int, int>>();
	srand((int)time(NULL));
}

forward_list<int>* PriceDepthList::StringToIntArray(string str)
{
	forward_list<int>* l = new forward_list<int>();
	forward_list<int>::iterator it = l->before_begin();
	int acc = 0;
	for (int i = 0; i < (int)str.length(); i++)
	{
		if (str[i] == ' ')
		{
			it = l->insert_after(it, acc);
			acc = 0;
			continue;
		}
		acc = acc * 10 + (str[i] - '0');
	}
	l->insert_after(it, acc);
	return l;
}

void PriceDepthList::SplitLineIntoBuysAndSells(string line, LinkedList<pair<int, int>> *buys, LinkedList<pair<int, int>> *sells)
{
	forward_list<int> *l = StringToIntArray(line);

	auto popFront = [](forward_list<int> *l)
	{
		int front = l->front();
		l->pop_front();
		return front;
	};

	auto getNextPair = [=](forward_list<int> *l)
	{
		int first = popFront(l);
		int second = popFront(l);
		return new pair<int, int>(first, second);
	};

	int numBuys = popFront(l);
	int numSells = popFront(l);

	while (numBuys > 0)
	{
		buys->PushBack(getNextPair(l));
		numBuys--;
	}

	while (numSells > 0)
	{
		sells->PushBack(getNextPair(l));
		numSells--;
	}

	delete l;
}

string PriceDepthList::ParseString(string line)
{
	LinkedList<pair<int, int>> newBuys;
	LinkedList<pair<int, int>> newSells;
	SplitLineIntoBuysAndSells(line, &newBuys, &newSells);

	int buyChanges;
	string buyString = GetChanges(buys, &newBuys, buyChanges);

	int sellChanges;
	string sellString = GetChanges(sells, &newSells, sellChanges);

	stringstream ss;
	ss << buyChanges << " " << sellChanges << buyString << sellString;
	
	return ss.str();
}

string PriceDepthList::GetChanges(LinkedList<pair<int, int>> *list, LinkedList<pair<int, int>> *news, int& numchanges)
{
	LinkedList<pair<int, int>> changes;
	LinkedList<pair<int, int>>::iterator newsIt = news->begin();
	if (newsIt == news->end())
	{
		while (!list->Empty())
		{
			pair<int, int> *p = list->PopFront();
			p->second = 0;
			changes.PushBack(p);
		}
	}
	for (LinkedList<pair<int, int>>::iterator it = list->begin(); newsIt != news->end(); )
	{
		if (it == list->end())
		{
			list->PushBack(*newsIt);
			changes.PushBack(new pair<int, int>(*news->Remove(newsIt)));
		}
		else if (list == buys && (*newsIt)->first > (*it)->first || list == sells && (*newsIt)->first < (*it)->first)
		{
			it = list->InsertBefore(it, *newsIt);
			changes.PushBack(new pair<int, int>(*news->Remove(newsIt)));
		}
		else if ((*newsIt)->first == (*it)->first)
		{
			if ((*newsIt)->second != (*it)->second)
			{
				(*it)->second = (*newsIt)->second;
				changes.PushBack(news->Remove(newsIt));
			}
			else
			{
				pair<int, int> *p = news->Remove(newsIt);
				delete p;
			}
			it++;
		}
		else
		{
			pair<int, int> *remove = list->Remove(it);
			remove->second = 0;
			changes.PushBack(remove);
		}
	}
	numchanges = changes.size();
	return ToString(&changes);
}

void PriceDepthList::ParseChangesOnly(string line)
{
	LinkedList<pair<int, int>> buyChanges;
	LinkedList<pair<int, int>> sellChanges;
	SplitLineIntoBuysAndSells(line, &buyChanges, &sellChanges);

	ParseChangesSingleList(buys, &buyChanges);
	ParseChangesSingleList(sells, &sellChanges);
}

void PriceDepthList::ParseChangesSingleList(LinkedList<pair<int, int>> *list, LinkedList<pair<int, int>> *news)
{
	LinkedList<pair<int, int>>::iterator newsIt = news->begin();
	for (LinkedList<pair<int, int>>::iterator it = list->begin(); newsIt != news->end(); )
	{
		if (it == list->end() && (*newsIt)->first != 0)
		{
			list->PushBack(news->Remove(newsIt));
		}
		else if (list == buys && (*newsIt)->first > (*it)->first || list == sells && (*newsIt)->first < (*it)->first)
		{
			it = list->InsertBefore(it, news->Remove(newsIt));
		}
		else if ((*it)->first == (*newsIt)->first)
		{
			if ((*newsIt)->second == 0)
			{
				pair<int, int> *remove = list->Remove(it);
				delete remove;
			}
			else
			{
				(*it)->second = (*newsIt)->second;
				it++;
			}
			newsIt++;
		}
		else
		{
			it++;
			continue;
		}
	}
}

int PriceDepthList::GetRandomQty()
{
	int number = 1 + rand() % 9;
	int power = 2 + rand() % 4;
	return (int)(number * pow(10, power));
}

int PriceDepthList::Length(LinkedList<pair<int, int>> *l)
{
	int num = 0;
	for (LinkedList<pair<int, int>>::iterator it = l->begin(); it != l->end(); it++)
	{
		num++;
	}
	return num;
}

void PriceDepthList::MakeRandomChanges(LinkedList<pair<int, int>> *l)
{
	int change = rand() % 6;
	int numAdd = change - Length(l);

	while (numAdd < 0)
	{
		pair<int, int> *remove = l->PopFront();
		delete remove;
		numAdd++;
	}
	
	int boundaryPrice = l == buys ? 30 : 31;
	int adjustment = l == buys ? 1 : -1;
	
	while (numAdd > 0)
	{
		if (Length(l) == 0)
		{
			l->PushFront(new pair<int, int>(boundaryPrice, GetRandomQty()));
			numAdd--;
		}

		for (LinkedList<pair<int, int>>::iterator it = l->begin(); it != l->end() && numAdd > 0; it++)
		{
			if (it.next() == l->end() || abs((*it)->first - (*it.next())->first) > 1)
			{
				l->InsertAfter(it, new pair<int, int>((*it)->first - adjustment, GetRandomQty()));
				numAdd--;
			}
			else if (it == l->begin() && abs(boundaryPrice - (*it)->first) > 0)
			{
				l->PushFront(new pair<int, int>((*it)->first + adjustment, GetRandomQty()));
				numAdd--;
			}
		}
	}
}

void PriceDepthList::MakeRandomChanges()
{
	MakeRandomChanges(buys);
	MakeRandomChanges(sells);
}

string PriceDepthList::ToString(LinkedList<pair<int, int>> *l)
{
	stringstream ss;
	for (LinkedList<pair<int, int>>::iterator it = l->begin(); it != l->end(); it++)
	{
		ss << " " << (*it)->first << " " << (*it)->second;
	}
	return ss.str();
}

string PriceDepthList::ToString()
{
	stringstream ss;
	ss << Length(buys) << " " << Length(sells) << ToString(buys) << ToString(sells);
	return ss.str();
}

PriceDepthList::~PriceDepthList()
{
	delete buys;
	delete sells;
}
