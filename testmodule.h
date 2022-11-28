#ifndef TESTMODULE_H
#define TESTMODULE_H

//CUSTOM INCLUDES
#include <module.h>

class TestMod : Module
{
public:
    //Inherited methods
    void setID(int in) override;
    int getID() override;
    std::string getName() override;
    //Methods
    TestMod();
    virtual ~TestMod();
};
#endif // TESTMODULE_H
