//
// Created by Shawn Manuel on 30/12/2017.
//

#ifndef SERVERPROGRAM_LINKEDLIST_H
#define SERVERPROGRAM_LINKEDLIST_H

#include <cstdlib>

using namespace std;

template <class T> 
class LinkedList
{
	public:
		class Node
		{
			public:
				T *value;
				Node *next;
				Node(T *v, Node *n) { value = v; next = n; }
		};

		class iterator
		{
			private:

			public:
				Node *curr;
				Node *prev;
				iterator() {}
				iterator(Node *c, Node *p) { curr = c; prev = p; }
				T* operator *() { return curr->value; }
				bool operator ==(iterator other) { return curr == other.curr; }
				bool operator !=(iterator other) { return !(*this == other); }
				iterator next() { return iterator(curr->next, curr); }
				iterator& operator ++(int)
				{
					prev = curr;
					curr = curr->next;
					return *this;
				}
		};

		LinkedList()
		{
			head = nullptr;
			tail = nullptr;
		}

		bool Empty()
		{
			return head == nullptr;
		}

		int size()
		{
			int size = 0;
			for (iterator it = begin(); it != end(); it++, size++) { }
			return size;
		}

		iterator InsertAfter(iterator it, T *value)
		{
			if (it == end())
			{
				throw "Cannot insert after end";
			}

			Node *added = new Node(value, it.curr->next);
			if (it.curr == tail)
			{
				tail = added;
			}
			it.curr->next = added;
			return it++;
		}

		iterator InsertBefore(iterator it, T *value)
		{
			Node *added = new Node(value, it.curr);
			if (it.curr == head && it.prev == nullptr)
			{
				head = added;
				if (tail == nullptr)
				{
					tail = added;
				}
			}
			else
			{
				it.prev->next = added;
			}
			it.prev = added;
			return it;
		}

		T* Remove(iterator& it)
		{
			if (it == end())
			{
				throw "Cannot remove end";
			}

			if (it.curr == tail)
			{
				tail = it.prev;
			}

			if (it.curr == head)
			{
				head = head->next;
			}
			else
			{
				it.prev->next = it.curr->next;
			}
			Node *remove = it.curr;
			it.curr = it.curr->next;
			T *value = remove->value;
			delete remove;
			return value;
		}

		iterator PushFront(T *value)
		{
			Node *added = new Node(value, head);
			if (tail == nullptr)
			{
				tail = added;
			}
			head = added;
			return iterator(added, nullptr);
		}

		T* PopFront()
		{
			if (head == nullptr)
			{
				throw "Cannot pop from empty list";
			}

			if (tail == head)
			{
				tail = head->next;
			}
			Node *remove = head;
			head = head->next;
			T *value = remove->value;
			delete remove;
			return value;
		}

		iterator PushBack(T *value)
		{
			Node *added = new Node(value, nullptr);
			iterator it = iterator(added, tail);
			if (tail == nullptr)
			{
				head = added;
			}
			else
			{
				tail->next = added;
			}
			tail = added;
			return it;
		}

		iterator begin()
		{
			return iterator(head, nullptr);
		}

		iterator end()
		{
			return iterator(nullptr, tail);
		}

		void Clear()
		{
			while (!Empty())
			{
				PopFront();
			}
		}

		~LinkedList()
		{
			while (!Empty())
			{
				T* val = PopFront();
				delete val;
			}
		}

	private:
		Node *head;
		Node *tail;
};


#endif //SERVERPROGRAM_LINKEDLIST_H