#ifndef BACKBONE_H
#define BACKBONE_H

/* CUSTOM INCLUDES */
#include <module.h>
#include <workorder.h>
#include <message.h>

/* PATH INCLUDES */

/* USING */

/* FORWARD CLASS DECL'S */

/****************************** BACKBONE ******************************/
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
/****************************** END BACKBONE ******************************/

#endif // BACKBONE_H
