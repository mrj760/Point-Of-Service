#include "backbone.h"

Backbone::Backbone()
{
    moduleList = LoadModuleList();
    loadUnloaded(moduleList);
}

Backbone::~Backbone()
{

}


map<string, int> loadModuleList();
string loadModule(string ModName, int ModID);
map<int, string> loadUnloaded();

void Backbone::receiveMsg(Message msg)
{

}

void Backbone::sendMsg(Message msg)
{

}

void Backbone::postJob(WorkOrder wo)
{

}

bool Backbone::checkJobs(Module& mod)
{

}

WorkOrder Backbone::takeJob(Module& mod)
{

}

int Backbone::getID()
{

}
