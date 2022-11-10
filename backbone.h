#ifndef BACKBONE_H
#define BACKBONE_H

/* CUSTOM INCLUDES */
#include <module.h>
#include <workorder.h>
#include <message.h>
#include <map>

/* PATH INCLUDES */

/* USING */

/* FORWARD CLASS DECL'S */

/****************************** BACKBONE ******************************/
class Backbone : Module
{
public:
//Methods
    Backbone();
    virtual ~Backbone();

    void receiveMsg(Message msg);
    void sendMsg(Message msg);

    void postJob(WorkOrder wo);
    WorkOrder takeJob(Module& mod);
    WordOrder checkJobs(Module& mod);
    int getID();

//Variables

private:
//Methods

//Variables
	map<string, int> ModuleList;
	map<int, WorkOrder> JobList;	
	

};
/****************************** END BACKBONE ******************************/

#endif // BACKBONE_H
