#include <testmodule.h>
#include <backbone.h>

TestMod::TestMod()
{
    this->_ID = Backbone::modCount;
    this->name = "TST";
}
TestMod::~TestMod()
{
    Backbone::modCount--;
}

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

bool TestMod::receive(WorkOrder& wo)
{
    try {
        std::cout << wo.data.getText().data();
    } catch (std::exception e) {
        return false;
    }
    return true;
}
