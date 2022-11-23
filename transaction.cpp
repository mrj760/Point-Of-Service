#include "transaction.h"


// TODO
void Transaction::setFinalPrice(int)
{

}

// TODO
void Transaction::addItem(Item item, int qty)
{

}

// TODO
void Transaction::removeItem(Item item, int qty)
{

}

// TODO
int Transaction::contains(const Item &item)
{
    return -1;
}

QString Transaction::itemsAsString()
{
    QString ret;
    for (tuple<Item, int> tup : items)
    {
        ret += QString::number(std::get<0>(tup).sku) + ",";
        ret += QString::number(std::get<1>(tup)) + ",";
    }
    return ret;
}

// TODO
bool Transaction::operator==(const Transaction& other)
{
    return false;
}

// TODO
Transaction Transaction::operator=(const Transaction& c)
{
    return Transaction(c);
}
