#include "customer.h"

Customer::Customer()
{

}

int Customer::getID() const
{
    return ID;
}

void Customer::setID(int newID)
{
    if (ID == newID)
        return;
    ID = newID;
    emit IDChanged();
}

const qstring &Customer::getName() const
{
    return name;
}

void Customer::setName(const qstring &newName)
{
    if (name == newName)
        return;
    name = newName;
    emit nameChanged();
}

const qstring &Customer::getAddress() const
{
    return address;
}

void Customer::setAddress(const qstring &newAddress)
{
    if (address == newAddress)
        return;
    address = newAddress;
    emit addressChanged();
}
