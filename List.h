#ifndef list_h
#define list_h
#include <iostream>
#include "ListNode.h"

using namespace std;

template<class DATATYPE>

class List
{
public:
	//constructers/destructers
	List(DATATYPE newData);
	List();
	~List();

	static ListNode<DATATYPE>* search(ListNode<DATATYPE>* node, DATATYPE target);
	void printList();
	int getLength();
	bool isEmpty();
	
	bool pushFront(DATATYPE newData);
	bool pushBack(DATATYPE newData);
	bool pushInOrder(DATATYPE newDATA);

	DATATYPE popFront();
	DATATYPE popBack();

	bool remove(DATATYPE target);
	bool makeEmpty();

	ListNode<DATATYPE>* find(DATATYPE target);
	DATATYPE top();

private:
	ListNode<DATATYPE>* head;
	ListNode<DATATYPE>* tail;
	int listLength;
};


template<class DATATYPE>
List<DATATYPE>::List(DATATYPE newData = NULL)
{ //incase data is provided
	if(newData == NULL)
	{
		head = NULL;
		tail = NULL;
		listLength = 0;
	}
	else
	{
		head = new ListNode<DATATYPE>*(newData);
		tail = head;
		listLength = 1;
	}
}

template<class DATATYPE>
List<DATATYPE>::List()
{//default constructor
	head = NULL;
	tail = NULL;
	listLength = 0;
}

template<class DATATYPE>
List<DATATYPE>::~List()
{ //uses make empty function to clear list
	makeEmpty();
}

template<class DATATYPE>
ListNode<DATATYPE>* List<DATATYPE>::search(ListNode<DATATYPE>* node, DATATYPE target)
{ //node is the root node (or the starting node)
	ListNode<DATATYPE>* tempnode = node;

	while(tempnode->data != target)
	{ //checks each element one by one to find it, then once it does, returns it
		tempnode = tempnode->next;
	}
	return tempnode;
}

template<class DATATYPE>
void List<DATATYPE>::printList()
{ //prints the list with spacing between each node
	ListNode<DATATYPE>* tempnode = head;

	while(tempnode->next != NULL)
	{
		cout << tempnode->data << " "; // << " -> ";
		tempnode = tempnode->next;
	}
	cout << tempnode->data;
	cout << endl;
}

template<class DATATYPE>
int List<DATATYPE>::getLength()
{ //returns length
	return listLength;
}

template<class DATATYPE>
bool List<DATATYPE>::makeEmpty()
{
	if(head == NULL && tail == NULL) //makes sure head and tail are real before running
		return false;
	ListNode<DATATYPE>* tempnode;
	if(head != NULL) //double checking
		tempnode = head;  //assign tempnode
	if(tempnode->next == NULL)
	{ //checks if tempnode is last node
		delete tempnode;
		head = NULL;
		tail = NULL;
		return true;
	}
	ListNode<DATATYPE>* oldnode;
	oldnode = head;
	while(tempnode != NULL)
	{
		oldnode = tempnode;
		if(tempnode->next != NULL)
			tempnode = tempnode->next;
		else
			tempnode = NULL;
		delete oldnode;
		listLength -= 1;
	}
	tail = NULL;
	head = NULL;
	return true;
}

template<class DATATYPE>
bool List<DATATYPE>::pushFront(DATATYPE newData)
{
	ListNode<DATATYPE>* newNode = new ListNode<DATATYPE>(newData);
	if(newNode == NULL)
		return false; //incase memory didn't allocate
	if(head == NULL)
	{ //if list is empty
		head = newNode;
		tail = newNode;
	}
	else if(head == tail)
	{//list has 1 node
		head = newNode;
		newNode->next = tail;
	}
	else
	{ //anything else
		newNode->next = head;
		head = newNode;
	}
	listLength++; //increase integer list length
	return true;
}

template<class DATATYPE>
bool List<DATATYPE>::pushInOrder(DATATYPE newData)
{
	ListNode<DATATYPE>* newNode = new ListNode<DATATYPE>(newData);
	ListNode<DATATYPE>* tempNode = head;
	if(newNode == NULL)
		return false; //no memory allocated
	if(head == NULL)
	{ //list empty
		head = newNode;
		tail = newNode;
	}
	else if(head == tail)
	{ //list has 1 lement
		if(newData == head->data)
			return true; // if node already exists
		else if(newData > head->data)
		{
			tail = newNode;
			newNode->prev = head;
			head->next = tail;
		}
		else if(newData < head->data)
		{
			head = newNode;
			newNode->next = tail;
		}
	}
	else
	{
		while((tempNode != NULL) && (newData > tempNode->Data))
		{
			if(tempNode->getData() == newData)
				return false;
			(tempNode->next)->prev = newNode;
			(tempNode->prev)->next = newNode;
		}
	}
	listLength++; //increase length
	return true;
}

template<class DATATYPE>
bool List<DATATYPE>::pushBack(DATATYPE newData)
{
	ListNode<DATATYPE>* newNode = new ListNode<DATATYPE>(newData);
	if(newNode == NULL)//memory not allocated
		return false;
	if((head == tail) && head == NULL)
	{ //list empty
		head = newNode;
		tail = newNode;
	}
	else if(head == tail)
	{//1 node
		tail = newNode;
		tail->prev = head;
		head->next = tail;
	}
	else
	{//else
		tail->next = newNode;
		newNode->prev = tail;
		tail = newNode;
	}
	listLength++;
	return true;
}

template<class DATATYPE>
DATATYPE List<DATATYPE>::popFront()
{
	DATATYPE tempdata = head->data;
	ListNode<DATATYPE>* tempNode = head;
	if(head->next != NULL)
	{
		head = head->next;
	}
	else
	{
		head = NULL;
		tail = NULL;
		delete tempNode;
		tempNode = NULL;
		listLength--; //decrease length
		return tempdata;
	}
	if((tempNode->next == tail) && (tail != NULL))
	{
		head = tail;
		head->next = NULL;
		tail->prev = NULL;
		delete tempNode;
	}
	else if((tempNode->next == tempNode->prev) && tempNode->next == NULL)
	{ //if next node is empty, set head/tail pointers to null
		head = NULL;
		tail = NULL;
		delete tempNode;
	}
	else
	{

		head->prev = NULL;
		delete tempNode;
		tempNode = NULL;
	}
	
	
	listLength--; //decrease length
	return tempdata;
}

template<class DATATYPE>
DATATYPE List<DATATYPE>::popBack()
{
	DATATYPE tempdata = NULL;
	ListNode<DATATYPE>* tempNode = head;
	for(; tempNode->next != this->tail; tempNode = tempNode->next); //find back, I didn't use my previous pointer on this for some reason, idk why
	tempdata = (tempNode->next)->data;
	delete tempNode->next;
	if(tempNode == NULL)
	{
		head = NULL;
		tail = NULL;
	}
	else
		tail = tempNode;
	listLength--;
	return tempdata;
}

template<class DATATYPE>
bool List<DATATYPE>::remove(DATATYPE target)
{
	ListNode<DATATYPE>* tempNode = head;
	ListNode<DATATYPE>* oldNode = NULL;
	if(head->data == tail->data == target)
	{ //if 1 node and that node is the target
		delete head;
		head = NULL;
		tail = NULL;

	}
	else if(head->data == target)
	{ //if head is the target
		ListNode<DATATYPE>* tempNode = head;
		head = head->next;
		if(tempNode->next == NULL)
		{
			head = NULL;
			tail = NULL;
		}
		else
			head = tempNode->next;
		delete tempNode;
		
	}
	else if(tail->data == target)
	{ //if tail is the target
		ListNode<DATATYPE>* tempNode = head;
		for(; tempNode->next != this->tail; tempNode = tempNode->next);
		if(tempNode->next == NULL)
		{
			head = NULL;
			tail = NULL;
		}
		else
			tail = tempNode->next;
		delete tempNode->next;
		return tempdata;
	}
	else
	{ //otherwise
		for(; (tempNode != NULL) && ((tempNode->next)->data != target); tempNode = tempNode->next);
		if(tempNode == NULL)
			return false;
		oldNode = tempNode;
		tempNode->next = (tempNode->next)->next;
		listLength--;
		delete oldNode;
	}
}

template<class DATATYPE>
ListNode<DATATYPE>* List<DATATYPE>::find(DATATYPE target)
{
	ListNode<DATATYPE>* tempNode1 = head;
	ListNode<DATATYPE>* tempNode2 = tail;
	if(tempNode1 == NULL) //checks to make sure tempNode1 is not NULL (if head is null)
		return NULL;
	else if((tempNode1 == tail) && (tempNode1->data == target))
		return head; //checks if 1 node, and if that node the the target
	else if((tempNode1 == tail) && (tempNode1->data != target))
		return NULL; //checks if 1 node, and if not the target
	else if(tempNode1->data == target)
		return tempNode1; //if tempnode is target
	else if(tempNode2->data == target)
		return tempNode2;
	else if(tempNode1->next == tempNode2)
		return NULL; //checks 2 nodes, and we've already tested both at this point
	else
	{
		do {
			tempNode1 = tempNode1->next; //advances both pointers (closing in on middle)
			tempNode2 = tempNode2->prev;
			if((tempNode1->data == target) || (tempNode2->data == target))
			{ //checks if either are the target
				if(tempNode1->data == target)
					return tempNode1;
				else
					return tempNode2;
			}
			if(tempNode1->next == tempNode2)
				return NULL; //checks if they are going to overlap (even # of nodes)
		}while(tempNode1 != tempNode2);
		if(tempNode1->data == target)
			return tempNode1; //for list lengths that are odd
		return NULL;
	}
	return NULL;
}

template<class DATATYPE>
DATATYPE List<DATATYPE>::top()
{ //returns the front nodes data
	return head->data;
}

template<class DATATYPE>
bool List<DATATYPE>::isEmpty()
{
	if((head == tail) && head == NULL)
		return true;
	return false;
}

#endif