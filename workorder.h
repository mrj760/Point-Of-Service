#ifndef WORKORDER_H
#define WORKORDER_H
#include <message.h>

class WorkOrder
{
public:
	virtual	Message getCommand();
	virtual Message getData();
	virtual Message getSecurity();
	int ID;
};

#endif // WORKORDER_H
