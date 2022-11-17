#ifndef WORKORDER_H
#define WORKORDER_H
#include <message.h>

class WorkOrder
{
public:
	virtual	Message* getCommand();
	virtual Message* getData();
	virtual Message* getSecurity();
	int ID;
	bool operator ==(WorkOrder wo){
		if (this->getCommand() == wo.getCommand())
			if (this->getData() == wo.getData())
				if (this->ID == wo.ID)
					return true;
		return false;
	}
};

#endif // WORKORDER_H
