#ifndef BACKBONE_H
#define BACKBONE_H

/* CUSTOM INCLUDES */
#include <module.h>
#include <workorder.h>
#include <message.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <tuple>

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

    void postJob(WorkOrder& wo);
    WorkOrder& takeJob(Module& mod);
    bool checkJobs(Module& mod);
    int getID(std::string module);
    static int modCount;
    //Variables

private:
    //Methods
    std::map<std::string, int> loadModuleList(std::string filename);
    std::string loadModule(std::string ModName, int ID);
    std::map<int, std::string> loadUnloaded(std::map<std::string, int> allModules);
    void endModule(int ID);

    //Variables
    std::map<std::string, int> moduleList;
    std::map<int, WorkOrder&> jobList;


};
/****************************** END BACKBONE ******************************/

#endif // BACKBONE_H
