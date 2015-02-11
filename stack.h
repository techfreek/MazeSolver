#ifndef stack_h
#define stack_h

#include"List.h"

template<class DATATYPE>
class stack
{
public:
	stack();
	~stack();
	bool isEmpty();
	bool push(DATATYPE newData);
	DATATYPE pop();
	bool contains(DATATYPE target);
	void printStack();
	DATATYPE top();
	bool clearList();
	void reverseStack();
	//this uses my List.h and ListNode.h classes that I made. these interface with them
	//this is so I can rely on one generalized templated linked list, then I can make tweeks to this
private:
	List<DATATYPE>* head;
};



template<class DATATYPE>
stack<DATATYPE>::stack()
{ // new List
	head = new List<DATATYPE>();
}

template<class DATATYPE>
stack<DATATYPE>::~stack()
{ //empties list in list.h
	head->makeEmpty();
}

template<class DATATYPE>
bool stack<DATATYPE>::isEmpty()
{
	return head->isEmpty();
}

template<class DATATYPE>
bool stack<DATATYPE>::push(DATATYPE newData)
{
	return head->pushFront(newData);
}

template<class DATATYPE>
DATATYPE stack<DATATYPE>::pop()
{
	return head->popFront();
}
template<class DATATYPE>
bool stack<DATATYPE>::clearList()
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
DATATYPE stack<DATATYPE>::top()
{
	return head->top();
}

template<class DATATYPE>
void stack<DATATYPE>::printStack()
{
	head->printList();
}

template<class DATATYPE>
void stack<DATATYPE>::reverseStack()
{
	List<DATATYPE>* newList = new List<DATATYPE>();
	DATATYPE temp = NULL;
	while(!head->isEmpty() != NULL)
	{
		temp = head->popFront();
		newList->pushFront(temp);
	}
	head = newList;
}


#endif