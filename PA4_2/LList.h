#pragma once
#include"List.h"

template<class DATATYPE>

//this uses my List.h and ListNode.h classes that I made. these interface with them
//this is so I can rely on one generalized templated linked list, then I can make tweeks to this
class LList
{
public:
	LList();
	~LList();
	bool isEmpty();
	void print();
	int getLength();
	bool insert(DATATYPE newData);
	bool remove(DATATYPE oldData);
	bool contains(DATATYPE target);
	DATATYPE top();
	bool clearList();
	ListNode<DATATYPE>* find(DATATYPE target);

private:
	List<DATATYPE>* head;
};

template<class DATATYPE>
LList<DATATYPE>::LList()
{ // new List
	head = new List<DATATYPE>();
}

template<class DATATYPE>
LList<DATATYPE>::~LList()
{ //empties list in list.h
	head->makeEmpty();
}

template<class DATATYPE>
bool LList<DATATYPE>::isEmpty()
{
	if(head == NULL)
		return true;
	return false;
}
template<class DATATYPE>
void LList<DATATYPE>::print()
{
	head->print();
}

template<class DATATYPE>
int LList<DATATYPE>::getLength()
{
	return head->getLength();
}

template<class DATATYPE>
bool LList<DATATYPE>::insert(DATATYPE newData) //push back
{
	return head->pushBack(newData);
}

template<class DATATYPE>
bool LList<DATATYPE>::remove(DATATYPE oldData)
{
	return head->remove(oldData);
}
template<class DATATYPE>
bool LList<DATATYPE>::clearList()
{
	if(head != NULL)
	{
		head->makeEmpty(); //deletes all node
		head == NULL; //sets points to NULL
		return true;
	}
	else
		return false;
}

template<class DATATYPE>
bool LList<DATATYPE>::contains(DATATYPE target)
{
	if(head->find(target) != NULL) //find returns a node, but I don't want that in this case
		return true;
	return false;
}

template<class DATATYPE>
DATATYPE LList<DATATYPE>::top()
{
	return head->top();
}

template<class DATATYPE>
ListNode<DATATYPE>* LList<DATATYPE>::find(DATATYPE target)
{
	return head->find(target);
}