#ifndef listnode_h
#define listnode_h

template<class DATATYPE>

class ListNode
{
public:
	ListNode(DATATYPE datavalue, ListNode* nextptr, ListNode* prevptr);
	ListNode(const DATATYPE & item);
	void setData(DATATYPE newData);
	DATATYPE getData();
	DATATYPE data;  // data
	ListNode<DATATYPE>* next; //not proper data hiding procedures, I know
	ListNode<DATATYPE>* prev;
};

template<class DATATYPE>
ListNode<DATATYPE>::ListNode(DATATYPE datavalue = NULL, ListNode<DATATYPE>* nextptr = NULL, ListNode<DATATYPE>* prevptr = NULL)
{
	this->data = datavalue;
	this->next = nextptr;
	this->prev = prevptr;
}

template<class DATATYPE>
ListNode<DATATYPE>::ListNode(const DATATYPE & item)
{
	data = item;
	next = NULL;
	prev = NULL;
}

template<class DATATYPE>
void ListNode<DATATYPE>::setData(DATATYPE newData)
{
	this->data = newData;
}

template<class DATATYPE>
DATATYPE ListNode<DATATYPE>::getData()
{
	return this->data;
}

#endif