//#include "LinkedList.h"
//
//
//template <class T>
//LinkedList<T>::LinkedList()
//{
//	head = nullptr;
//	tail = nullptr;
//}
//
//template<class T>
//typename LinkedList<T>::iterator LinkedList<T>::InsertAfter(typename LinkedList<T>::iterator it, T value)
//{
//	if (it == end())
//	{
//		throw "Cannot insert after end";
//	}
//
//	Node *added = new Node(value, it.curr->next);
//	if (it.curr == tail)
//	{
//		tail = added;
//	}
//	it.curr->next = added;
//	return it++;
//}
//
//template<class T>
//typename LinkedList<T>::iterator LinkedList<T>::InsertBefore(typename LinkedList<T>::iterator it, T value)
//{
//	Node *added = new Node(value, it.curr);
//	if (it.curr == head && it.prev == nullptr)
//	{
//		head = added;
//		if (tail == nullptr)
//		{
//			tail = added;
//		}
//	}
//	else
//	{
//		it.prev->next = added;
//	}
//	it.prev = added;
//	return it++;
//}
//
//template<class T>
//T& LinkedList<T>::Remove(typename LinkedList<T>::iterator it, T value)
//{
//	if (it == end())
//	{
//		throw "Cannot remove end";
//	}
//
//	if (it == tail)
//	{
//		tail = it.prev;
//	}
//	Node *remove = it.curr;
//	it.prev->next = it.curr->next;
//	T& value = remove->value;
//	delete remove;
//	return value;
//}
//
//template<class T>
//typename LinkedList<T>::iterator LinkedList<T>::PushFront(T value)
//{
//	Node *added = new Node(value, head);
//	if (tail == nullptr)
//	{
//		tail = added;
//	}
//	head = added;
//	return iterator(added);
//}
//
//template<class T>
//T& LinkedList<T>::PopFront()
//{
//	if (head == nullptr)
//	{
//		return nullptr;
//	}
//
//	if (tail == head)
//	{
//		tail = head->next;
//	}
//	Node *remove = head;
//	head = head->next;
//	T& value = remove->value;
//	delete remove;
//	return value;
//}
//
//template<class T>
//typename LinkedList<T>::iterator LinkedList<T>::begin()
//{
//	return iterator(head, nullptr);
//}
//
//template<class T>
//typename LinkedList<T>::iterator LinkedList<T>::end()
//{
//	return iterator(nullptr, tail);
//}
//
//template <class T>
//LinkedList<T>::~LinkedList()
//{
//}
