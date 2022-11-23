#include <pos.h>


POS::POS()
{
}

Item POS::readSKU(const QString& sku)
{
    return Item();
}


bool POS::activateCart(int ID)
{
    return false;
}

void POS::deactivateCart()
{
}

bool POS::finalizeCart()
{
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
