#include <pos.h>


POS::POS()
{
    this->_ID = Backbone::modCount;
    this->name = "POS";
    this->waiting = true; //Shouldn't things start as waiting? I'll ask Nathan later
}

POS::~POS()
{
    Backbone::modCount--;
}

Item POS::readSKU(const QString& sku)
{
    std::string sku_as_text = sku.toStdString();
    Message sku_request = Message();
    sku_request.fill("Requires ");
    sku_request.add(sku_as_text);
    //Backbone.postJob(sku_request);
    return Item();
}


bool POS::activateCart(int ID)
{
    return false;
}

void POS::deactivateCart()
{
    //Where do inactive cards go?
}

bool POS::finalizeCart()
{
    /*
    if(_activeCart exists)
    {
        //Will finalize cart in here
    }
    */
    return false;
}

bool POS::activateRegister(int ID)
{
    return false;
}

void POS::deactivateRegister()
{
}

bool POS::addCashToRegister(int cents)
{
    return false;
}

bool POS::subCashFromRegister(int cents)
{
    return false;
}

int POS::getID()
{
    return _ID;
}

void POS::setID(int id)
{
    _ID = id;
}

std::string POS::getName()
{
    return this->name;
}

bool POS::setWaiting()
{
    waiting = true;
    return waiting;
}

bool POS::receive(WorkOrder& wo)
{
    bool success = true;
    waiting = false;//Job has begun

    std::cout << "We got the job Carl!" << std::endl; //This is to test job passing I guess

    //Implementing actually acting on the job
    //Checking job type
    if(wo.getCommand()->type() == Message::contains_cmd)
    {
        //do the command
    }
    else if(wo.getCommand()->type() == Message::contains_db_entry)
    {
        //process db entry
    }

    //Call is done, thus the POS can wait again
    setWaiting();

    return success;
}
