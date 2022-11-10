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
    bool checkJobs(Module& mod);
    int getID();

//Variables

private:
//Methods
    map<string, int> loadModuleList();
    string loadModule(string ModName, int ModID);
    map<int, string> loadUnloaded();

//Variables
	map<string, int> moduleList;
	map<int, WorkOrder> jobList;
	

};
/****************************** END BACKBONE ******************************/

#endif // BACKBONE_H
