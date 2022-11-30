#ifndef MODULE_H
#define MODULE_H
#include <string>
#include <workorder.h>
class Module {
protected:
    int _ID;
    std::string name;
public :
    bool waiting=false;
    virtual int getID()=0;
    virtual void setID(int id)=0;
    virtual std::string getName()=0;
    //Use this to update waiting flag.
    virtual bool setWaiting()=0;
    //Backbone will use this to deliver jobs
    virtual bool receive(WorkOrder& wo);
};

#endif //MODULE_H
