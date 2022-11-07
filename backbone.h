#ifndef BACKBONE_H
#define BACKBONE_H

#include "workorder.h"
#include "message.h"

class Backbone : Module
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
