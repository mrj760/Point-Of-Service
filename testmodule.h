#ifndef TESTMODULE_H
#define TESTMODULE_H

//CUSTOM INCLUDES
#include <module.h>

class TestMod : public Module
{
public:
    //Inherited methods
    void setID(int in) override;
    int getID() override;
    std::string getName() override;
    //Methods
    TestMod();
    ~TestMod();
};
#endif // TESTMODULE_H
