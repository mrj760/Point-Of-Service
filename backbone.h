#ifndef BACKBONE_H
#define BACKBONE_H
#include "WorkOrder.h"
#include "Message.h"

class Module : Backbone
{
public:	
	Backbone();
	
	void receiveMsg(Message msg);
	void sendMsg(Message msg);

	void postJob(WorkOrder wo);
	WorkOrder takeJob(Module mod);
	
	
private: 
	
	
};

#endif // BACKBONE_H
