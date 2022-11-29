#include "backbone.h"

#define POS_MODULE_NAME "POS"
#define GUI_MODULE_NAME "GUI"
#define DB_MODULE_NAME "DB"
#define PMT_MODULE_NAME "PMT"
#define TST_MODULE_NAME "TEST"

int Backbone::modCount = 0;

Backbone::Backbone()
{
    this->_ID=modCount;
    modCount++;


}
Backbone::Backbone(std::string filename)
{
    this->_ID=modCount;
    modCount++;
    std::map<std::string,int> moduleList = loadModuleList(filename);
    loadUnloaded(moduleList);
}
Backbone::~Backbone()
{

}
// INHERITED METHODS
void Backbone::setID(int in){
    this->_ID = in;
}
int Backbone::getID(){
    return this->_ID;
}
std::string Backbone::getName(){
    return this->name;
}

std::map<std::string, int> Backbone::loadModuleList(std::string filename)
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

void Backbone::addModule(Module& mod)
{
    try{
    if(mod.getID()==0){
        mod.setID(modCount);
        moduleList.insert({mod.getID(),mod});
        std::cout << mod.getName()+" Module inserted with ID# " + std::to_string(mod.getID());
    }
    }
    catch(std::exception e){
        std::cout << "Unable to add module\n";
        throw e;}
}

//Still not sure how to use this to load modules from file data
//For this to work, the modules will probably have to be their
//own executables which take backbone info as CL args.
void Backbone::loadModule(std::string ModName, int ID)
{
    if(ModName == POS_MODULE_NAME){
        //new POS(ID);
        std::cout << "POS Loaded. ID= "<<ID<<std::endl;
        Backbone::modCount++;
    }
    if(ModName == GUI_MODULE_NAME){
        //new GUI(ID);
        std::cout << "GUI Loaded. ID= "<<ID<<std::endl;
        Backbone::modCount++;
    }
    if(ModName == DB_MODULE_NAME){
        //new DB(ID);
        std::cout << "DB Loaded. ID= "<<ID<<std::endl;
        Backbone::modCount++;
    }
    if(ModName == PMT_MODULE_NAME){
        //new PMT(ID);
        std::cout << "PMT Loaded. ID= "<<ID<<std::endl;
        Backbone::modCount++;
    }
    if(ModName == TST_MODULE_NAME){
        //new PMT(ID);
        std::cout << "PMT Loaded. ID= "<<ID<<std::endl;
        Backbone::modCount++;
    }

}


std::map<std::string, int> Backbone::loadUnloaded(std::map<std::string,int> allModules)
{

    std::map<std::string, int>::iterator it = allModules.begin();
    while(it != allModules.end()){
        if(it->second == 0){
            loadModule(it->first, Backbone::modCount);
        }
    }

    return std::map<std::string, int>(); // - needed a return value - micah
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
    //Use iterator to ensure 'wo' is not a duplicate order.
    std::map<int , WorkOrder&>::iterator it = jobList.begin();
    while(it != jobList.end()){
        if( it->first == wo.ID && it->second == &wo)    return;
    }
    jobList.insert({wo.ID, wo});
}

bool Backbone::checkJobs(Module& mod)
{
    std::map<int , WorkOrder&>::iterator it = jobList.begin();
    while(it != jobList.end()){
        if( it->first == mod.getID())   return true;
    }
    return false;
}

WorkOrder& Backbone::takeJob(Module& mod)
{
    
    std::map<int , WorkOrder&>::iterator it = jobList.begin();
    while(it != jobList.end()){
        if( it->first == mod.getID()){
            WorkOrder& temp = it->second;
            jobList.erase(it);
            return temp;
        }
    }
    throw "Failed to take job for this module." ;
}

int Backbone::getIDFromList(std::string modname)
{
    std::map<int, Module&>::iterator it = moduleList.begin();
    while(it != moduleList.end()){
        if(it->second.getName() == modname){
            return it->first;
        }
    }
    return 0;
}
