#ifndef WORKORDER_H
#define WORKORDER_H
#include message.h

class WorkOrder
{
public:
	vitual	Message getCommand();
	virtual Message getData();
	virtual Message getSecurity();

};

#endif // WORKORDER_H
