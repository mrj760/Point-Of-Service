#ifndef BACKBONE_H
#define BACKBONE_H

/* CUSTOM INCLUDES */
#include <module.h>
#include <workorder.h>
#include <message.h>

/* PATH INCLUDES */
#include <iostream>
#include <fstream>
#include <sstream>
#include <exception>
#include <map>
#include <tuple>
/* USING */

/* FORWARD CLASS DECL'S */

/****************************** BACKBONE ******************************/
class Backbone : public Module
{
public:
    //Inherited methods
    void setID(int in) override;
    int getID() override;
    std::string getName() override;
    //Methods
    Backbone();
    Backbone(std::string filename);
    virtual ~Backbone();

    void receiveMsg(Message msg);
    void sendMsg(Message msg);
    void postJob(WorkOrder& wo);
    WorkOrder& takeJob(Module& mod);
    bool checkJobs(Module& mod);
    int getIDFromList(std::string module);
    void addModule(Module& mod);
    bool deliver(Module& mod, WorkOrder wo);
    static int modCount;
    //Variables

private:
    //Methods
    std::map<std::string, int> loadModuleList(std::string filename);
    void loadModule(std::string ModName, int ID);
    std::map<std::string, int> loadUnloaded(std::map<std::string, int> allModules);
    void endModule(int ID);

    //Variables
    std::map<int, Module&> moduleList;
    std::map<int, WorkOrder&> jobList;


};
/****************************** END BACKBONE ******************************/

#endif // BACKBONE_H
