#include <testmodule.h>
#include <backbone.h>

void TestMod::setID(int in)
{
    this->_ID = in;
}

int TestMod::getID()
{
    return this->_ID   ;
}
std::string TestMod::getName()
{
    return this->name;
}
//Methods
TestMod::TestMod()
{
    this->_ID = Backbone::modCount;
    this->name = "TST";
}
TestMod::~TestMod()
{
    Backbone::modCount--;
}
