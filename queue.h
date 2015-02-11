#ifndef queue_h
#define queue_h

#include"List.h"

template<class DATATYPE>
class queue
{
public:
	queue();
	~queue();
	bool isEmpty();
	bool enqueue(DATATYPE newData);
	DATATYPE dequeue();
	void printQueue();
	DATATYPE top();
	bool clearQueue();
	//this uses my List.h and ListNode.h classes that I made. these interface with them
	//this is so I can rely on one generalized templated linked list, then I can make tweeks to this
private:
	List<DATATYPE>* head;
};



template<class DATATYPE>
queue<DATATYPE>::queue()
{ // new List
	head = new List<DATATYPE>();
}

template<class DATATYPE>
queue<DATATYPE>::~queue()
{ //empties list in list.h
	head->makeEmpty();
}

template<class DATATYPE>
bool queue<DATATYPE>::isEmpty()
{
	return head->isEmpty();
}

template<class DATATYPE>
bool queue<DATATYPE>::enqueue(DATATYPE newData)
{
	return head->pushBack(newData);
}

template<class DATATYPE>
DATATYPE queue<DATATYPE>::dequeue()
{
	return head->popFront();
}
template<class DATATYPE>
bool queue<DATATYPE>::clearQueue()
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
DATATYPE queue<DATATYPE>::top()
{
	return head->top();
}

template<class DATATYPE>
void queue<DATATYPE>::printQueue()
{
	head->printList();
}


#endif