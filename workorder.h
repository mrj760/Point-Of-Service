#ifndef WORKORDER_H
#define WORKORDER_H
#include <message.h>

class WorkOrder
{
    WorkOrder();
    virtual ~WorkOrder();
public:
	virtual	Message* getCommand();
	virtual Message* getData();
	virtual Message* getSecurity();
    int ID;
    Message command;
    Message data;
    Message security;
    bool operator ==(WorkOrder* wo){
//        return (getCommand() == wo.getCommand() && getData() == wo.getData() && ID == wo.ID);
        return (getCommand() == wo->getCommand() && getData() == wo->getData() && ID == wo->ID);
    }
};

#endif // WORKORDER_H
