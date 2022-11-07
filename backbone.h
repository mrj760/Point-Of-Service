#ifndef BACKBONE_H
#define BACKBONE_H

#include <module.h>
#include <workorder.h>
#include <message.h>

class Backbone : Module
{
public:
    Backbone();
    virtual ~Backbone();

    void receiveMsg(Message msg);
    void sendMsg(Message msg);

    void postJob(WorkOrder wo);
    WorkOrder takeJob(Module& mod);

    int getID();


private:


};

#endif // BACKBONE_H
