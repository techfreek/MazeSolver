#include "mazeNode.h"

mazeNode::mazeNode(int key)
{
	northD = true;
	northPtr = NULL;

	southD = true;
	southPtr = NULL;

	eastD = true;
	eastPtr = NULL;
	
	westD = true;
	westPtr = NULL;

	ID = key;
	status = 0;
}

mazeNode::~mazeNode()
{
	status = 0;
}