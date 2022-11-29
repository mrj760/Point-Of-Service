#ifndef MODULE_H
#define MODULE_H
#include <string>
class Module {
protected:
    int _ID;
    std::string name;
public :
    virtual int getID()=0;
    virtual void setID(int id)=0;
    virtual std::string getName()=0;
};

#endif //MODULE_H
