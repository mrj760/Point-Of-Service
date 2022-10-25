#ifndef ITEM_H
#define ITEM_H
#include <QString>

class Item
{


private:
    QString id;     // SKU ( ID )
    QString name;   // Name of item
    double qty;     // Quantity
    bool sellsByUnit; // Whether item is sold one at a time or in decimal amounts (e.g. cuts of wire)


public:
    /* Constructors */
    Item(QString id, QString name, double qty, bool sellsByUnit) :
        id(id), name(name), qty(qty), sellsByUnit(sellsByUnit) {};
    Item(QString id, QString name, int qty, bool sellsByUnit) :
        id(id), name(name), qty(qty), sellsByUnit(sellsByUnit) {};

    /* ID Functions */
    QString getId() const;

    /* Quantity Functions */
    double getQty() const;
    void setQty(double qty);
    void setQty(int qty);
    void subQty(double qty);
    void subQty(int qty);
    void addQty(double qty);
    void addQty(int qty);

    /* Sells By Unit Functions */
    bool getSellsByUnit() const;
    void setSellsByUnit(bool newSellsByUnit);
};

#endif // ITEM_H

