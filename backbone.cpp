#include "backbone.h"

#define POS_MODULE_NAME "POS"
#define GUI_MODULE_NAME "GUI"
#define DB_MODULE_NAME "DB"
#define PMT_MODULE_NAME "PMT"


Backbone::Backbone()
{
    std::map<std::string,int> moduleList = loadModuleList("modules.txt");
    loadUnloaded(moduleList);
}

Backbone::~Backbone()
{

}

std::map<std::string, int> loadModuleList(std::string filename)
{
    std::string filepath = "./" + filename;
    std::ifstream inFile;
    inFile.open(filepath);
    std::string line;
    std::string key;
    double value;
    std::map <std::string, int> params;
    while ( inFile.good() ){
        std::getline(inFile, line);
        std::istringstream ss(line);
        ss >> key >> value; // set the variables  
        params[key] = value; // input them into the map 
    }
    inFile.close();
    return params;

}

std::string loadModule(std::string ModName, int ID)
{
    if(ModName == POS_MODULE_NAME){
        //new POS(ID);
        std::cout << "POS Loaded. ID= "<<ID<<std::endl;
        return "POS";
    }
    if(ModName == GUI_MODULE_NAME){
        //new GUI(ID);
        std::cout << "GUI Loaded. ID= "<<ID<<std::endl;
        return "GUI";
    }
    if(ModName == DB_MODULE_NAME){
        //new DB(ID);
        std::cout << "DB Loaded. ID= "<<ID<<std::endl;
        return "DB";
    }
    if(ModName == PMT_MODULE_NAME){
        //new PMT(ID);
        std::cout << "PMT Loaded. ID= "<<ID<<std::endl;
        return "PMT";
    }

}

std::map<std::string, int> loadUnloaded(std::map<std::string,int> allModules)
{

    std::map<std::string, int>::iterator it = allModules.begin();
    while(it != allModules.end()){
        if(it->second == 0){
            loadModule(it->first, Backbone::modCount);
            Backbone::modCount++;
        }
    }
}

void Backbone::endModule(int ID)
{
    Backbone::modCount--;
}


//JOBLIST USES FORMAT OF:	std::map<int, WorkOrder> jobList
void Backbone::receiveMsg(Message msg)
{

}

void Backbone::sendMsg(Message msg)
{

}

void Backbone::postJob(WorkOrder& wo)
{
    std::map<int , WorkOrder>::iterator it = jobList.begin();
    while(it != jobList.end()){
        if( it->first == wo.ID && it->second == wo)    return;
    }
    jobList.insert({wo.ID,wo});
}

bool Backbone::checkJobs(Module& mod)
{

}

WorkOrder Backbone::takeJob(Module& mod)
{

}

int Backbone::getID(std::string modname)
{
    return moduleList[modname];
}
